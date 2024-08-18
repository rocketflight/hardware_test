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
#include "HardwareTest.h"

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
  Max
};

class DisplayST7735 : public HardwareTest
{
public:
  DisplayST7735();
  bool Init(Stream *port);
  void Run();
  void Read();

private:
  Adafruit_ST7735 _tft = Adafruit_ST7735(TFT_CS_PIN, TFT_DC_PIN, TFT_MOSI_PIN, TFT_SCLK_PIN, TFT_RST_PIN);

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

  TftTest _test = Lines;

  const __FlashStringHelper *_tftLabel[11] = {F("Lines"),
                                              F("Text"),
                                              F("Fast"),
                                              F("Rectangles"),
                                              F("FilledRectangles"),
                                              F("Circles"),
                                              F("FilledCircles"),
                                              F("Triangles"),
                                              F("RoundRectangles"),
                                              F("Print"),
                                              F("Media")};

  const __FlashStringHelper *_tftText = F("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere.");
};

#endif