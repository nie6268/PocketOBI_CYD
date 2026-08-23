// User_Setup.h for TFT_eSPI - ESP32-2432S028 "CYD" (ILI9341 clone panel)
// Paste this as the FULL content of <TFT_eSPI library folder>/User_Setup.h

#define ILI9341_2_DRIVER   // alternate ILI9341 driver for the clone chip on
                           // this board (see Bodmer/TFT_eSPI issue #1172)

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST  -1        // tied to 3V3 on this board
#define TFT_BL   21
#define TFT_BACKLIGHT_ON HIGH

#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

#define SPI_FREQUENCY       40000000
#define SPI_READ_FREQUENCY  20000000
#define USE_HSPI_PORT        // leaves VSPI free for the XPT2046 touch chip