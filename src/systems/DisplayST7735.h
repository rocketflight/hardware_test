/***************************************************************************
  This is a simple test for the RocketFlight Motion Pack TFT Display

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Depends on the following libraries:
  ----> https://github.com/adafruit/Adafruit-ST7735-Library

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef DISPLAY_TFT_ST7735_h
#define DISPLAY_TFT_ST7735_h

#include <Adafruit_ST7735.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>

#include "HardwareTest.h"
#include "AltimeterBMP388.h"

#define SML_FONT &FreeSans9pt7b
#define MED_FONT &FreeSans12pt7b
#define LGE_FONT &FreeSansBold18pt7b
#define TFT_WIDTH 160
#define TFT_HEIGHT 80

enum TftTest
{
  Lines,
  Text,
  Fast,
  Rects,
  FillRects,
  Circles,
  FillCircles,
  Triangles,
  RoundRects,
  Print,
  Media,
  Pressure,
  Max
};

class DisplayST7735 : public HardwareTest
{
public:
  DisplayST7735();
  bool Init(Stream *port, PrintMode mode, BaroData *data);
  void Run();
  void Read();
  void SetBaroData(BaroData *pdata);

private:
  Adafruit_ST7735 _tft = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_MOSI_PIN, TFT_SCLK_PIN, TFT_RST_PIN);

  void DrawPressure();
  void DrawLines(uint16_t color);
  void DrawText(char *text, uint16_t color);
  void DrawFastLines(uint16_t color1, uint16_t color2);
  void DrawRects(uint16_t color);
  void DrawFilledRects(uint16_t color1, uint16_t color2);
  void DrawCircles(uint8_t radius, uint16_t color);
  void DrawFilledCircles(uint8_t radius, uint16_t color);
  void DrawTriangles();
  void DrawRoundRects();
  void DrawPrint();
  void DrawMedia();

  BaroData *_data = nullptr;
  PrintMode _mode = PrintMode::PERIODIC_ALL;
  TftTest _test = Lines;
  GFXcanvas16 _canvas;

  const __FlashStringHelper *_tftLabel[12] = {F("Lines"),
                                              F("Text"),
                                              F("Fast"),
                                              F("Rectangles"),
                                              F("FilledRectangles"),
                                              F("Circles"),
                                              F("FilledCircles"),
                                              F("Triangles"),
                                              F("RoundRectangles"),
                                              F("Print"),
                                              F("Media"),
                                              F("Pressure")};

  const __FlashStringHelper *_tftText = F("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere.");
};

#endif