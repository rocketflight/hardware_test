/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack TFT Display

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/adafruit/Adafruit-ST7735-Library

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "DisplayST7735.h"

DisplayST7735::DisplayST7735() : _canvas(TFT_WIDTH, TFT_HEIGHT) {};

bool DisplayST7735::Init(Stream *port, PrintMode mode = PrintMode::PERIODIC_ALL, BaroData *data = nullptr)
{
  HardwareTest::Init(port);

  this->_data = data;
  this->_mode = mode;

  pinMode(TFT_CS_PIN, OUTPUT);
  pinMode(TFT_RST_PIN, OUTPUT);
  pinMode(TFT_CS_PIN, OUTPUT);

  _tft.initR(INITR_MINI160x80_PLUGIN);
  _tft.setSPISpeed(TFT_SPI_SPEED);
  _tft.setRotation(1); // Landscape
  _tft.fillScreen(ST77XX_BLACK);
  _tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  // Wait for screen to clear
  delay(50);

  // Enable backlight
  pinMode(TFT_LED_PIN, OUTPUT);
  digitalWrite(TFT_LED_PIN, HIGH);

  this->_initialised = true;
  this->Info(F("ST7735 TFT screen: is initialised"));
  return true;
}

void DisplayST7735::Run()
{
}

void DisplayST7735::Read()
{
  if (!this->IsOk())
  {
    this->Error(F("ST7735 TFT screen: is offline"));
    return;
  }

  switch (_mode)
  {
  case PrintMode::CONTINUOUS_AIR_PRESSURE_READING:
    _test = TftTest::Pressure;
    break;
  case PrintMode::CONTINUOUS_ALTIMETER_READING:
  case CONTINUOUS_MPU_ACCEL_GYRO_READING:
  case CONTINUOUS_MPU_QUARTERNION_READING:
  default:
    _test = _test >= TftTest::Max ? TftTest(0) : TftTest(_test + 1);
  }

  switch (_test)
  {
  case TftTest::Lines:
    DrawLines(ST77XX_YELLOW);
    break;
  case TftTest::Text:
    DrawText((char *)_tftText, ST77XX_WHITE);
    break;
  case TftTest::Fast:
    DrawFastLines(ST77XX_RED, ST77XX_BLUE);
    break;
  case TftTest::Rects:
    DrawRects(ST77XX_GREEN);
    break;
  case TftTest::FillRects:
    DrawFilledRects(ST77XX_YELLOW, ST77XX_MAGENTA);
    break;
  case TftTest::Circles:
    DrawCircles(10, ST77XX_BLUE);
    break;
  case TftTest::FillCircles:
    DrawFilledCircles(10, ST77XX_BLUE);
    break;
  case TftTest::Triangles:
    DrawTriangles();
    break;
  case TftTest::RoundRects:
    DrawRoundRects();
    break;
  case TftTest::Print:
    DrawPrint();
    break;
  case TftTest::Media:
    DrawMedia();
    break;
  case TftTest::Pressure:
    DrawPressure();
    break;
  default:
    _test = TftTest::Lines;
    DrawLines(ST77XX_YELLOW);
    break;
  };

  _port->printf("%d\tST7735 screen: %s\n", millis(), _tftLabel[_test]);
}

void DisplayST7735::DrawPressure()
{
  int16_t x1, y1, x = 0, y = 0;
  uint16_t w, h;

  if (!this->IsOk())
  {
    this->Error(F("ST7735 TFT screen: is offline"));
    return;
  }

  if (this->_data == nullptr)
  {
    this->Error(F("ST7735 TFT screen: barometer is offline"));
    return;
  }

  _canvas.fillScreen(ST77XX_BLACK);
  _canvas.setTextWrap(false);

  // pressure
  String str = String(this->_data->pressure, 2);
  _canvas.setFont(LGE_FONT);
  _canvas.getTextBounds(str, 0, 80, &x1, &y1, &w, &h);
  x = TFT_WIDTH / 2 - w / 2;
  y = TFT_HEIGHT / 2 + h / 2;
  _canvas.setCursor(x, y);
  _canvas.setTextColor(ST77XX_BLUE);
  _canvas.print(str);

  // temp
  str = String(F("Temp: ")) + String(this->_data->temperature, 1) + String(F(" C"));
  _canvas.setFont(SML_FONT);
  _canvas.getTextBounds(str, 0, 80, &x1, &y1, &w, &h);
  x = TFT_WIDTH / 2 - w / 2;
  y = h;
  _canvas.setCursor(x, y);
  _canvas.setTextColor(ST77XX_YELLOW);
  _canvas.print(str);

  // min / max
  str = String(this->_data->pressureMin, 2) + String(F(" / ")) + String(this->_data->pressureMax, 2);
  _canvas.setFont(SML_FONT);
  _canvas.getTextBounds(str, 0, 80, &x1, &y1, &w, &h);
  x = TFT_WIDTH / 2 - w / 2;
  y = TFT_HEIGHT - 1;
  _canvas.setCursor(x, y);
  _canvas.setTextColor(ST77XX_YELLOW);
  _canvas.print(str);

  _tft.drawRGBBitmap(0, 0, _canvas.getBuffer(), _canvas.width(), _canvas.height());
}

void DisplayST7735::DrawLines(uint16_t color)
{
  _tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < _tft.width(); x += 6)
  {
    _tft.drawLine(0, 0, x, _tft.height() - 1, color);
  }
  for (int16_t y = 0; y < _tft.height(); y += 6)
  {
    _tft.drawLine(0, 0, _tft.width() - 1, y, color);
  }
}

void DisplayST7735::DrawText(char *text, uint16_t color)
{
  _tft.fillScreen(ST77XX_BLACK);
  _tft.setCursor(0, 0);
  _tft.setTextColor(color);
  _tft.setTextWrap(true);
  _tft.setTextSize(1);
  _tft.print(text);
}

void DisplayST7735::DrawFastLines(uint16_t color1, uint16_t color2)
{
  _tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < _tft.height(); y += 5)
  {
    _tft.drawFastHLine(0, y, _tft.width(), color1);
  }
  for (int16_t x = 0; x < _tft.width(); x += 5)
  {
    _tft.drawFastVLine(x, 0, _tft.height(), color2);
  }
}

void DisplayST7735::DrawRects(uint16_t color)
{
  _tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < _tft.height(); x += 6)
  {
    _tft.drawRect(_tft.width() / 2 - x / 2, _tft.height() / 2 - x / 2, x, x, color);
  }
}

void DisplayST7735::DrawFilledRects(uint16_t color1, uint16_t color2)
{
  _tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = _tft.height() - 1; x > 6; x -= 6)
  {
    _tft.fillRect(_tft.width() / 2 - x / 2, _tft.height() / 2 - x / 2, x, x, color1);
    _tft.drawRect(_tft.width() / 2 - x / 2, _tft.height() / 2 - x / 2, x, x, color2);
  }
}

void DisplayST7735::DrawFilledCircles(uint8_t radius, uint16_t color)
{
  _tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = radius; x < _tft.width(); x += radius * 2)
  {
    for (int16_t y = radius; y < _tft.height(); y += radius * 2)
    {
      _tft.fillCircle(x, y, radius, color);
    }
  }
}

void DisplayST7735::DrawCircles(uint8_t radius, uint16_t color)
{
  _tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < _tft.width() + radius; x += radius * 2)
  {
    for (int16_t y = 0; y < _tft.height() + radius; y += radius * 2)
    {
      _tft.drawCircle(x, y, radius, color);
    }
  }
}

void DisplayST7735::DrawTriangles()
{
  _tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = _tft.width() / 2;
  int x = _tft.height() - 1;
  int y = 0;
  int z = _tft.width();
  for (t = 0; t <= 15; t++)
  {
    _tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void DisplayST7735::DrawRoundRects()
{
  _tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int x = 0;
  int y = 0;
  int w = _tft.width() - 2;
  int h = _tft.height() - 2;
  while ((w > 10) && (h > 10))
  {
    _tft.drawRoundRect(x, y, w, h, 5, color);
    x += 2;
    y += 3;
    w -= 4;
    h -= 6;
    color += 1100;
  }
}

void DisplayST7735::DrawPrint()
{
  _tft.fillScreen(ST77XX_BLACK);
  _tft.setTextWrap(false);
  _tft.fillScreen(ST77XX_BLACK);
  _tft.setCursor(0, 0);
  _tft.setTextColor(ST77XX_RED);
  _tft.setTextSize(1);
  _tft.println(F("Hello World!"));
  _tft.setTextColor(ST77XX_YELLOW);
  _tft.setTextSize(2);
  _tft.println(F("Hello World!"));
  _tft.setTextColor(ST77XX_GREEN);
  _tft.setTextSize(3);
  _tft.println(F("Hello World!"));
  _tft.setTextColor(ST77XX_BLUE);
  _tft.setTextSize(4);
  _tft.print(1234.567);
}

void DisplayST7735::DrawMedia()
{
  // play
  _tft.fillScreen(ST77XX_BLACK);
  _tft.fillRoundRect(0, 10, 78, 60, 8, ST77XX_WHITE);
  _tft.fillTriangle(17, 20, 17, 60, 65, 40, ST77XX_RED);

  // pause
  _tft.fillRoundRect(82, 10, 78, 60, 8, ST77XX_WHITE);
  _tft.fillRoundRect(96, 18, 20, 45, 5, ST77XX_GREEN);
  _tft.fillRoundRect(127, 18, 20, 45, 5, ST77XX_GREEN);

  // play color
  _tft.fillTriangle(17, 20, 17, 60, 65, 40, ST77XX_BLUE);

  // pause color
  _tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  _tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  _tft.fillTriangle(17, 20, 17, 60, 65, 40, ST77XX_GREEN);
}
