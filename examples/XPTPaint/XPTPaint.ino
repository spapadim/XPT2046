/*
 * Copyright (c) 2015-2016  Spiros Papadimitriou
 *
 * This file is part of github.com/spapadim/XPT2046 and is released
 * under the MIT License: https://opensource.org/licenses/MIT
 *
 * This software is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied.
 */

#include <Arduino.h>
#include <SPI.h>

#include <Ucglib.h>  // Required
#include <XPT2046.h>

// Modify the following two lines to match your hardware
// Also, update calibration parameters below, as necessary
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 2 , /*cs=*/ 4, /*reset=*/ 5);
XPT2046 touch(/*cs=*/ 16, /*irq=*/ 0);

void setup() {
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  //ucg.begin(UCG_FONT_MODE_SOLID);
  touch.begin(ucg.getWidth(), ucg.getHeight());  // Must be done before setting rotation
  ucg.setRotate270();
  touch.setRotation(touch.ROT270);
  ucg.clearScreen();

  // Replace these for your screen module
  touch.setCalibration(209, 1759, 1775, 273);
}

static uint16_t prev_x = 0xffff, prev_y = 0xffff;

void loop() {
  if (touch.isTouching()) {
    uint16_t x, y;
    touch.getPosition(x, y);
    if (prev_x == 0xffff) {
      ucg.drawPixel(x, y);
    } else {
      ucg.drawLine(prev_x, prev_y, x, y);
    }
    prev_x = x;
    prev_y = y;
  } else {
    prev_x = prev_y = 0xffff;
  }
  delay(20);
}
