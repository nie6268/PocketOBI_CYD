# PocketOBI - CYD (ESP32-2432S028) port

## Installation

1. **Arduino IDE**: install ESP32 board support (Espressif), board "ESP32 Dev Module".
2. Install libraries: **TFT_eSPI** (Bodmer), **XPT2046_Touchscreen** (Paul Stoffregen).
3. **Required step, easy to miss:** copy `TFT_eSPI_library_config/User_Setup.h`
   into your installed TFT_eSPI library folder, REPLACING the file there:
   - Windows: `Documents\Arduino\libraries\TFT_eSPI\User_Setup.h`
   - macOS:   `~/Documents/Arduino/libraries/TFT_eSPI/User_Setup.h`
   - Linux:   `~/Arduino/libraries/TFT_eSPI/User_Setup.h`

   Without this, `tft.init()` hangs forever (watchdog reset loop) - this
   board needs `ILI9341_2_DRIVER`, not the plain `ILI9341_DRIVER`, and the
   sketch-side "define before include" trick does NOT reach TFT_eSPI's own
   separately-compiled .cpp file in plain Arduino IDE builds.
4. Restart the Arduino IDE (so it picks up the changed library file).
5. Open `PocketOBI_CYD.ino` and upload.

## Wiring

DATA -> GPIO22, ENABLE -> GPIO27 (both with a 470 ohm-4.7k ohm pull-up to
3.3V), GND -> battery B-. Never connect B+ (18V).

## PC bridge mode (Open Battery Information / OBI-1 web app)

Works, but the OBI-1 web app decodes the temperature field as Celsius x100,
while this firmware (like several other independent implementations)
decodes it as 1/10 Kelvin (`T = raw/10 - 273.15`). Same raw byte, two
different unit assumptions - Makita never documented which is correct.
Trust whichever your own testing (e.g. an actual thermometer) confirms;
this is not a bug in the bridge, both sides get the identical byte.
