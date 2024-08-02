/***************************************************************************
  This is a config file for pinouts for the OpenRocketFlight Motion Pack

  Designed specifically to work with the Heltec Wireless Tracker V1.1
  ----> https://heltec.org/project/wireless-tracker/

  Written by David Skinner, July 2024

  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#ifndef HETLEC_WIRELESS_TRACKER_h
#define HETLEC_WIRELESS_TRACKER_h

#include <Arduino.h>

#define SEALEVELPRESSURE_HPA 1026.9 // 1 standard atmosphere is 1013.25hPa

#ifndef PI
#define PI 3.1415926
#endif

#define HARDWARE_VERSION "MOTION_PACK_V1_0"
#define VERBOSE false

#define SERIAL_WAIT_MILLIS 5000
#define SERIAL_BAUD 115200
#define LOOP_WAIT_MILLIS 5000
#define LOOP_CONTINUOUS_MILLIS 100

#define LED_MILLIS 100
#define LED_ON HIGH
#define LED_OFF LOW
#define LED_PIN 18

#define BUZZER_PIN 4
#define BUZZER_CHANNEL 1

#define TFT_LED_PIN 21
#define TFT_CS_PIN 38
#define TFT_RST_PIN 39
#define TFT_DC_PIN 40
#define TFT_SCLK_PIN 41
#define TFT_MOSI_PIN 42
#define TFT_SPI_SPEED 40000000L

#define RADIO_DIO_1_PIN 14
#define RADIO_NSS_PIN 8
#define RADIO_RESET_PIN 12
#define RADIO_BUSY_PIN 13
#define LORA_CLK_PIN 9
#define LORA_MISO_PIN 11
#define LORA_MOSI_PIN 10

#define GNSS_CTRL_PIN 3
#define GNSS_TX_PIN 33
#define GNSS_RX_PIN 34
#define GNSS_RST_PIN 35
#define GNSS_PPS_PIN 36
#define GNSS_BAUD 115200UL

#define VEXT_CTL_PIN 3
#define VAX77 2030

#define I2C_SDA_PIN 7
#define I2C_SCL_PIN 6
#define I2C_FREQUENCY_HZ 400000UL

#define BMP388_ALTIMETER_ADDR1 0x76 // Primary I2C address for the BMP388 altimeter
#define BMP388_ALTIMETER_ADDR2 0x77 // Backup I2C address for the BMP388 altimeter

#define MPU_INT_PIN 5                    // MPU interrupt pin
#define MPU_ACCEL_SCALE gpm16            // (ICM_20948_ACCEL_CONFIG_FS_SEL_e)
                                         // gpm2
                                         // gpm4
                                         // gpm8
                                         // gpm16
#define MPU_GYRO_SCALE dps1000           // (ICM_20948_GYRO_CONFIG_1_FS_SEL_e)
                                         // dps250
                                         // dps500
                                         // dps1000
                                         // dps2000
#define MPU_ACCEL_SAMPLE_RATE_DIVIDER 10 // Set the gyro sample rate divider 10 = 102Hz
                                         // ODR is computed as follows: 1.125 kHz/(1+ACCEL_SMPLRT_DIV[11:0]). 19 = 56.25Hz.
                                         // MPU_ACCEL_SAMPLE_RATE_DIVIDER 19 = 56.25Hz (InvenSense Nucleo example - 0x13)
                                         // MPU_ACCEL_SAMPLE_RATE_DIVIDER  8 = 125Hz
                                         // MPU_ACCEL_SAMPLE_RATE_DIVIDER  4 = 225Hz
#define MPU_GYRO_SAMPLE_RATE_DIVIDER 10  // Set the accel sample rate divider 10 = 100Hz
                                         // ODR is computed as follows: 1.1 kHz/(1+GYRO_SMPLRT_DIV[7:0]). 19 = 55Hz.
                                         // MPU_GYRO_SAMPLE_RATE_DIVIDER 19 = 55Hz (InvenSense Nucleo example - 0x13)
                                         // MPU_GYRO_SAMPLE_RATE_DIVIDER  8 = 112Hz
                                         // MPU_GYRO_SAMPLE_RATE_DIVIDER  4 = 220Hz

#endif

// #define WIFI_LoRa_32_V3 true
// #define DISPLAY_HEIGHT 80
// #define DISPLAY_WIDTH 160

// #ifndef HELTEC_TRACKER_V11_H_
// #define HELTEC_TRACKER_V11_H_

// #include <stdint.h>

// /* Heltec Wireless Tracker V1.1 */

// //
// // TFT data from HT_st7735.h
// //
// #define ST7735_CS_Pin           38
// #define ST7735_REST_Pin         39
// #define ST7735_DC_Pin           40
// #define ST7735_SCLK_Pin         41
// #define ST7735_MOSI_Pin         42
// #define ST7735_LED_K_Pin        21
// #define ST7735_VTFT_CTRL_Pin    3
// #define ST7735_WIDTH            160
// #define ST7735_HEIGHT           80
// // mini 160x80, rotate left (INITR_MINI160x80_PLUGIN)
// #define ST7735_MODEL            INITR_MINI160x80_PLUGIN

// //
// // SX1262 from esp32/libraries/LoraWan102/src/driver/board-config.h
// //
// #define BOARD_TCXO_WAKEUP_TIME  5
// #define RADIO_DIO_1             14
// #define RADIO_NSS               8
// #define RADIO_RESET             12
// #define RADIO_BUSY              13
// #define LORA_CLK                9
// #define LORA_MISO               11
// #define LORA_MOSI               10

// //
// // UC6580 GNSS
// //
// #define VGNSS_CTRL              3
// #define GNSS_TX                 33
// #define GNSS_RX                 34
// #define GNSS_RST                35
// #define GNSS_PPS                36
// #define GNSS_BAUD               115200UL

// //
// // misc from schematic
// //
// #define VEXT_CTRL               3
// #define VBAT_READ               1
// // VBAT = analogReadMilliVolts(VBAT_READ) * 4.9
// #define ADC_CTRL                2
// #define USER_KEY                0
// #define LED                     18
// #define GNSS_BOOT_MODE          47
// #define GNSS_D_SEL              48
// #define U0RXD                   44
// #define U0TXD                   43

// #define LED_PIN 18

// #define HELTEC_TRACKER_V1_X
// #define OPENROCKETFLIGHT_MOTION_PACK_V1

// // I2C
// #define I2C_SDA SDA
// #define I2C_SCL SCL

// // ST7735S TFT LCD
// #define ST7735S 1 // there are different (sub-)versions of ST7735
// #define ST7735_CS 38
// #define ST7735_RS 40  // DC
// #define ST7735_SDA 42 // MOSI
// #define ST7735_SCK 41
// #define ST7735_RESET 39
// #define ST7735_MISO -1
// #define ST7735_BUSY -1
// #define ST7735_BL_V05 21 /* V1.1 PCB marking */
// #define ST7735_SPI_HOST SPI3_HOST
// #define SPI_FREQUENCY 40000000
// #define SPI_READ_FREQUENCY 16000000
// #define SCREEN_ROTATE
// #define TFT_HEIGHT DISPLAY_WIDTH
// #define TFT_WIDTH DISPLAY_HEIGHT
// #define TFT_OFFSET_X 26
// #define TFT_OFFSET_Y -1
// #define SCREEN_TRANSITION_FRAMERATE 3 // fps
// #define DISPLAY_FORCE_SMALL_FONTS

// // pin 3 is Vext on v1.1 - HIGH enables LDO for Vext rail which goes to:
// // GPS UC6580:          GPS V_DET(8), VDD_IO(7), DCDC_IN(21), pulls up RESETN(17), D_SEL(33) and BOOT_MODE(34) through 10kR
// // GPS LNA SW7125DE:    VCC(4), pulls up SHDN(5) through 10kR
// // LED:                 VDD, LEDA (through diode)
// #define VEXT_ENABLE_V05 3 // active HIGH - powers the GPS, GPS LNA and OLED VDD/anode
// #define BUTTON_PIN 0

// #define BATTERY_PIN 1 // A battery voltage measurement pin, voltage divider connected here to measure battery voltage
// #define ADC_CHANNEL ADC1_GPIO1_CHANNEL
// #define ADC_ATTENUATION ADC_ATTEN_DB_2_5 // lower dB for high resistance voltage divider
// #define ADC_MULTIPLIER 4.9 * 1.045
// #define ADC_CTRL 2 // active HIGH, powers the voltage divider. Only on 1.1
// #define ADC_CTRL_ENABLED HIGH

// #undef GPS_RX_PIN
// #undef GPS_TX_PIN
// #define GPS_RX_PIN 33
// #define GPS_TX_PIN 34
// #define PIN_GPS_RESET 35
// #define PIN_GPS_PPS 36
// // #define PIN_GPS_EN 3    // Uncomment to power off the GPS with triple-click on Tracker v1.1, though we'll also lose the
// // display.

// #define GPS_RESET_MODE LOW
// #define GPS_UC6580

// #define USE_SX1262
// #define LORA_DIO0 -1 // a No connect on the SX1262 module
// #define LORA_RESET 12
// #define LORA_DIO1 14 // SX1262 IRQ
// #define LORA_DIO2 13 // SX1262 BUSY
// #define LORA_DIO3    // Not connected on PCB, but internally on the TTGO SX1262, if DIO3 is high the TXCO is enabled

// #define LORA_SCK 9
// #define LORA_MISO 11
// #define LORA_MOSI 10
// #define LORA_CS 8

// #define SX126X_CS LORA_CS
// #define SX126X_DIO1 LORA_DIO1
// #define SX126X_BUSY LORA_DIO2
// #define SX126X_RESET LORA_RESET

// #define SX126X_DIO2_AS_RF_SWITCH
// #define SX126X_DIO3_TCXO_VOLTAGE 1.8

// #endif // HELTEC_TRACKER_V11_H_