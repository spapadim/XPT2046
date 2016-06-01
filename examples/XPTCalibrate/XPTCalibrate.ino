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

#include <Ucglib.h>
#include <XPT2046.h>

// Modify the following two lines to match your hardware
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 2 , /*cs=*/ 4, /*reset=*/ 5);
XPT2046 touch(/*cs=*/ 16, /*irq=*/ 0);

static void calibratePoint(uint16_t x, uint16_t y, uint16_t &vi, uint16_t &vj) {
  // Draw cross
  ucg.setColor(0xff, 0xff, 0xff);
  ucg.drawHLine(x - 8, y, 16);
  ucg.drawVLine(x, y - 8, 16);
  while (!touch.isTouching()) {
    delay(10);
  }
  touch.getRaw(vi, vj);
  // Erase by overwriting with black
  ucg.setColor(0, 0, 0);
  ucg.drawHLine(x - 8, y, 16);
  ucg.drawVLine(x, y - 8, 16);
}

void calibrate() {
  uint16_t x1, y1, x2, y2;
  uint16_t vi1, vj1, vi2, vj2;
  touch.getCalibrationPoints(x1, y1, x2, y2);
  calibratePoint(x1, y1, vi1, vj1);
  delay(1000);
  calibratePoint(x2, y2, vi2, vj2);
  touch.setCalibration(vi1, vj1, vi2, vj2);

  char buf[80];
  snprintf(buf, sizeof(buf), "%d,%d,%d,%d", (int)vi1, (int)vj1, (int)vi2, (int)vj2);
  ucg.setFont(ucg_font_helvR14_tr);
  ucg.setColor(0xff, 0xff, 0xff);
  ucg.setPrintPos(0, 25);
  ucg.print("setCalibration params:");
  ucg.setPrintPos(0, 50);
  ucg.print(buf);
}

void setup() {
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  //ucg.begin(UCG_FONT_MODE_SOLID);
  touch.begin(ucg.getWidth(), ucg.getHeight());
  ucg.clearScreen();

  calibrate();  // No rotation!!
}

void loop() {
  // Do nothing
  delay(1000);
}
