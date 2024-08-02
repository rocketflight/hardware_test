/***************************************************************************
  This is a firmward load to test the OpenRocketFlight Motion Pack hardware.
  It is intended to be a simple, stand-alone test as to whether all sensors
  are connected properly and responding as expected.

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Arduino.h>
#include "systems/LedOnboard.h"
#include "systems/GnssUC6580.h"
#include "systems/AltimeterBMP388.h"
#include "systems/LoraSCX1262.h"
#include "systems/DisplayST7735.h"
#include "systems/MpuICM20948.h"
#include "systems/BatteryMAX17048.h"
#include "systems/BuzzerOnboard.h"

enum PrintMode
{
    CONTINUOUS_MPU_ACCEL_GYRO_READING,
    CONTINUOUS_MPU_QUARTERNION_READING,
    CONTINUOUS_ALTIMETER_READING,
    PERIODIC_ALL
};
const PrintMode mode = PrintMode::PERIODIC_ALL;

// forward declarations
void checkResult(bool result, String message);

LedOnboard led;
BuzzerOnboard buzzer;
AltimeterBMP388 altimeter;
GnssUC6580 gnss;
DisplayST7735 tft;
LoraSCX1262 lora;
MpuICM20948 mpu;
BatteryMAX17048 lipo;

long next = 0;

void setup()
{
    bool result;

    // show at least a sign of life
    led.Flash(3, 100);

    // set up serial comms
    Serial.begin(SERIAL_BAUD);
    Serial.printf("%lu\tOpenRocketFlight Hardware Test -> %s\n", millis(), HARDWARE_VERSION);
    Serial.printf("%lu\t------------------------------------------------------------\n", millis());

    // set up I2C comms
    result = Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, I2C_FREQUENCY_HZ);
    checkResult(result, "Onboard I2C: communications failed");

    // set up the onboard led
    result = led.Init(&Serial);
    checkResult(result, "Onboard LED: initialisation failed");

    // set up the tft screen
    result = tft.Init(&Serial);
    checkResult(result, "Onboard TFT screen: initialisation failed");

    // set up the onboard gnss
    result = gnss.Init(&Serial);
    checkResult(result, "Onboard gnss: initialisation failed");

    // set up the lora radio
    result = lora.Init(&Serial);
    checkResult(result, "Onboard LoRa radio: initialisation failed");

    // set up the altimeter
    result = altimeter.Init(&Serial, Wire);
    checkResult(result, "Motion pack altimeter: initialisation failed");

    // set up the motion processor
    result = mpu.Init(&Serial, Wire);
    checkResult(result, "Motion pack processor: initialisation failed");

    // set up the lipo fuel gauge
    result = lipo.Init(&Serial, Wire);
    checkResult(result, "Motion pack battery gauge: initialisation failed");

    // set up the buzzer
    result = buzzer.Init(&Serial);
    checkResult(result, "Onboard buzzer: initialisation failed");

    // initialisation succeeded
    Serial.printf("%lu\tInitialisation completed ok\n", millis());
}

void loop()
{
    // ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
    // ledcWriteNote(BUZZER_CHANNEL, NOTE_C, 4);
    // delay(500);
    // ledcWriteNote(BUZZER_CHANNEL, NOTE_D, 4);
    // delay(500);
    // ledcWriteNote(BUZZER_CHANNEL, NOTE_E, 4);
    // delay(500);
    // ledcWriteNote(BUZZER_CHANNEL, NOTE_F, 4);
    // delay(500);
    // ledcWriteNote(BUZZER_CHANNEL, NOTE_G, 4);
    // delay(500);
    // ledcWriteNote(BUZZER_CHANNEL, NOTE_A, 4);
    // delay(500);
    // ledcWriteNote(BUZZER_CHANNEL, NOTE_B, 4);
    // delay(500);
    // ledcDetachPin(BUZZER_PIN);

    // run frequently updated tasks
    gnss.Run();
    led.Run();
    mpu.Run();
    buzzer.Run();

    // periodically output readings
    if (millis() >= next)
    {
        switch (mode)
        {
        case CONTINUOUS_MPU_QUARTERNION_READING:
            next += LOOP_CONTINUOUS_MILLIS;
            mpu.ReadQuaternion();
            break;

        case CONTINUOUS_MPU_ACCEL_GYRO_READING:
            next += LOOP_CONTINUOUS_MILLIS;
            mpu.ReadAccelGyro();
            break;

        case CONTINUOUS_ALTIMETER_READING:
            next += LOOP_CONTINUOUS_MILLIS;
            altimeter.Read();
            break;

        default:
            next += LOOP_WAIT_MILLIS;
            Serial.printf("%lu\t------------------------------------------------------------\n", millis());
            Serial.printf("%lu\trunning tests...\n", millis());

            led.Read();
            buzzer.Read();
            tft.Read();
            altimeter.Read();
            gnss.Read();
            lipo.Read();
            mpu.Read();
            break;
        }
    }
}

void checkResult(bool result, String message)
{
    if (!result)
        Serial.printf("%lu\t%s :( ***\n", millis(), message.c_str());
}

void fatalRestart()
{
    bool state = HIGH;
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.printf("%lu\tRestarting in 5 seconds", millis());
    for (int i = 0; i < 100; i++)
    {
        state = state ? LOW : HIGH;
        digitalWrite(LED_BUILTIN, state);
        delay(50);
        Serial.print(".");
    }
    ESP.restart();
}

/* TODO
Stuff to work out:
9 axis MPU
fuel guage
ADC for voltage?
Low power mode
Flash RAM
Lora ping pong test
*/

// #include <Arduino.h>
// #include <Adafruit_ST7735.h>
// #include <TinyGPSPlus.h>
// #include <RadioLib.h>

// TinyGPSPlus gps;
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// void setup_gps()
// {
//     Serial1.begin(115200, SERIAL_8N1, GPS_RX, GPS_TX);
// }

// void setup_tft()
// {
//     pinMode(TFT_CS, OUTPUT);
//     pinMode(TFT_RST, OUTPUT);
//     pinMode(TFT_CS, OUTPUT);

//     tft.initR(INITR_MINI160x80_PLUGIN);
//     tft.setRotation(1); // Landscape
//     tft.fillScreen(ST77XX_BLACK);
//     tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

//     delay(50); // Wait for screen to clear

//     // Enable backlight
//     pinMode(TFT_LED, OUTPUT);
//     digitalWrite(TFT_LED, HIGH);
// }

// SPIClass radio_spi(FSPI);
// SPISettings spiSettings(2000000, MSBFIRST, SPI_MODE0);
// SX1262 radio = new Module(RADIO_NSS, RADIO_DIO_1, RADIO_RESET, RADIO_BUSY, radio_spi, spiSettings);
// LoRaWANNode node(&radio, &EU868);

// int setup_lorawan() {
//     pinMode(RADIO_NSS, OUTPUT);
//     radio_spi.begin(LORA_CLK, LORA_MISO, LORA_MOSI, RADIO_NSS);
//     int state = radio.begin();
//     // check state and handle potential errors, print debug messages, ...
//     // state == RADIOLIB_ERR_NONE means no error so far
//     if (state == RADIOLIB_ERR_NONE){
//     }
//     return state;
// }
// void setup()
// {
//     pinMode(LED_BUILTIN, OUTPUT);
//     digitalWrite(LED_BUILTIN, HIGH);
//     // Enable power to peripherals
//     pinMode(VEXT_CTL, OUTPUT);
//     digitalWrite(VEXT_CTL, HIGH);
//     setup_tft();
//     setup_gps();
//     setup_lorawan();
//     tft.setCursor(0, 0);
//     tft.print("GPS searching...");
//     digitalWrite(LED_BUILTIN, LOW);
// }
// void run_tasks(uint32_t ms)
// {
//     unsigned long start = millis();
//     do
//     {
//         while (Serial1.available())
//             gps.encode(Serial1.read());
//     } while (millis() - start < ms);
// }
// void loop()
// {
//     if (gps.time.isUpdated())
//     {
//         tft.setCursor(0, 0);
//         tft.printf("%04u-%02u-%02u %02u:%02u:%02u",
//                    gps.date.year(), gps.date.month(), gps.date.day(),
//                    gps.time.hour(), gps.time.minute(), gps.time.second());
//     }
//     if (gps.location.isUpdated())
//     {
//         tft.setCursor(0, 12);
//         tft.printf("Lat: % 3.6f\nLon: % 3.6f\n", gps.location.lat(), gps.location.lng());
//     }
//     if (gps.altitude.isUpdated())
//     {
//         tft.setCursor(0, 28);
//         tft.printf("Alt: %3.0fft ", gps.altitude.feet());
//     }
//     run_tasks(1000);
// }
