# Heltec Tracker Hardware Test

This is a platform.io project to perform initial test and integration of new sensors and functions in a simple & light weight test environment.

> :warning: **Work in Progress**: This code is under development so nothing is guaranteed to work!

The hardware config currently is:

- [Heltec Wireless Tracker Version 1.1](https://heltec.org/project/wireless-tracker/)
  - Unicore UC-6580 GNSS (GPS) receiver
  - Semtech SX1262 915MHz LoRa transceiver
  - 160x180 TFT display
  - onboard LED
- custom daughter-board containing:
  - Bosch Sensortec BMP-388 altimeter
  - Analog Devices MAX17048 lipo fuel gauge
  - TDK InvenSense ICM-20948 -9dof motion processor
  - 16Mb SPI NOR RAM
  - piezo buzzer
  - power and level shifting

Its intended that this code is just for basic 'lights on' testing of each sensor before integrating them into a 'real' firmware load such as [Meshtastic](https://github.com/meshtastic)
