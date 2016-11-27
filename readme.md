# Rocket Alarm Clock Arduino Hack

This repository contains the ardunio code to countdown and fire a rocket.

It contains a couple of checks and some `for` loops to create the illusion of a rocket launching into space. The rocket in question is a hacked [rocket alarm clock](https://www.amazon.co.uk/Science-Museum-Rocket-Alarm-Clock/dp/B002VZLA6U).

The inner workings have been removed and replaced with an ardunio and custom circuit board. Upon pressing the "snooze" button, the screen and code counts down to 0 and fires the rocket using the mechanism the alarm clock used.

## Set up

The code requires the following two libraries:

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)

The hardware consists of:

- Arduino Nano
- 128 x 64 Monochrome OLED display

