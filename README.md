# XPT2046

Arduino library for XPT2046 / ADS7843 touchscreen driver.

[![XPT on ESP video](http://i.imgur.com/seqKBYU.jpg)](https://youtu.be/ql9J21sBRgQ)

Although there are a couple of libraries for this chip out there (e.g., [UTouch](http://www.rinkydinkelectronics.com/library.php?id=55) and [elechouse/touch](https://github.com/elechouse/touch)), both of them used bitbanging (rather than hardware SPI) and neither of them supported differential mode.  However, on the ESP8266, unless the SPI bus is shared, there aren't enough pins for both the LCD and the touchscreen.  Hardware SPI is also much faster, thus strongly preferred for the LCD.  This was the initial motivation but, while at it, I also added differential mode support.

My implementation is based on [TI's technical note](http://www.ti.com/lit/an/sbaa036/sbaa036.pdf) and [TI's datasheet](http://www.ti.com/lit/ds/symlink/ads7843.pdf).  It has been tested on an XPT2046 (which is a clone), connected to an ESP8266 (Sparkfun Thing).

The examples require Ucglib, but it should be easy to rewrite them for a library of your choice.  Either way, you will also need to edit the parameters in the examples to match your setup.

Caveats:
* Single-ended mode is completely untested, although there is a relevant argument in `getPosition()`; if current draw is low, I may remove the option altogether
* Does not support SPI transactions (and neither does Ucglib), so if you're sharing the bus, you should be careful!  It so happens that parameters good for Ucglib on an ILI9431 are also good for this chip; YMMV.
* I'm not sure if all display modules have different touchscreen and LCD coordinates; mine did, and the code has been tested only for that configuration.
