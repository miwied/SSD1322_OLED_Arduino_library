# Fork information

This is a fork from
[wjklimek1's repo](https://github.com/wjklimek1/SSD1322_OLED_library), for more
details check out his repo. This fork focuses on the compatibility with the
Arduino framework (especially working with the ESP32 mcu).

## Changes compared to the original repo:

- Translated library to cpp
- Added a ESP32 + PlatformIO example
- Deleted the STM32F4 Example <br> <br>

---

# SSD1322 OLED library (Arduino compatibale)

Portable library for 256x64 OLED display with SSD1322 controller

Library is divided into three layers:

- Hardware driver - contains all hardware dependent functions wrappers.
- API - commands, initialization seqence, functions to change screen grayscale
  levels, color inversion, contrasct, etc. Uses only functions from hardware
  driver to send data to OLED.
- GFX - functions to draw on frame buffer. Drawing single pixels, graphic
  primitives, lines, bitmaps and fonts. Operates only on frame buffer. Only
  function that sends buffer to OLED calls API funtions.

<!--
# Provided example
Provided example is made for Nucleo F411RE development board with STM32F411RET6 MCU. Project was created in STM32CubeIDE. OLED is connected to following GPIOs:

| SSD1322 pin | STM32F411 GPIO | Nucleo pin |
| ------- | ------ | ----- |
| RESET   | PA0  | A0 |
| DC      | PA1  | A1 |
| CS      | PA4  | A2 |
| SPI SCK | PB0  | A3 |
| SPI MOSI| PA10 | D2 |

**Click image below to watch effect of example code on YouTube**
[![](http://img.youtube.com/vi/iXRTsFQyKdo/0.jpg)](http://www.youtube.com/watch?v=iXRTsFQyKdo "SSD1322 presentation")

# Examples with DMA

In a folder with examples for STM32F411 also two projects utilizing DMA data
strasfers were included. First one uses DMA in blocking mode, so CPU has to wait
for transmission end to leave a function. This still gives some preformance
boost, especially for frame buffer transfers.

In a second example DMA works in non blocking mode, so CPU only commissions DMA
transfer and then leaves function. That takes much less CPU time, but **library
in this example was changed slightly to handle CS pin in a different way.**

Following changes were made to enable non blocking mode DMA:

- CS pin is set high again in `SPI_TX_Completed()` callback
- CS pin is not set high again in API functions
- API functions using SPI directly wait with transmission untill previous one
  was finished by polling `SPI_transmission_finished` flag.

This gives considerable preformance boost when huge data blocks, like frame
buffer, are transfered. When DMA sends data through SPI, CPU can go on and do
other useful task.

# How to modify it to work with different MCU than STM32F411?

Due to layered structure of library you have to provide only following functions
in SSD1322_HW_driver.c file:

- drive RESET pin low and high
- drive CS (chip select) pin low and high
- drive DC (data/command) pin low and high
- send single byte via SPI interface
- send array of bytes via SPI interface
- delay milliseconds

Dont be afraid of that delay. It is only used in init sequence to drive RESET
pin low for a few milliseconds.

# SPI configuration

SSD1322 expects different SPI clock phase and polarity than CubeMX gives by
default. Setting should be following:

- clock polarity (CPOL) = High
- clock phase (CPHA) = 2 Edge
-->

# Adafruit fonts

GFX library can draw text with fonts provided by [AdafruitGFX][AdafruitGFX]
library. To write text with Adafruit font include font file and select font with
function:

```c
void select_font(const GFXfont *new_gfx_font)
```

for example:

```c
select_font(&FreeMono12pt7b);
```

When font is already selected you can use it to write text on screen. It works
only for null terminated strings!

# Bitmaps

Two bitmap formats are supported:

```c
void draw_bitmap_8bpp(uint8_t *frame_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size);
```

It draws bitmap where one pixel corresponds to one byte - just an 8bit grayscale
bitmaps.

```c
void draw_bitmap_4bpp(uint8_t *frame_buffer, const uint8_t *bitmap, uint16_t x0, uint16_t y0, uint16_t x_size, uint16_t y_size);
```

Here one byte in bitmap stores brightness value for two pixels - just like in
the actual framebuffer.

To convert bitmaps to 8 or 4 bits per pixel grayscale depth you can use
converter from [this link][converter], downloading software "Converting bitmap
to Hex". It's a bit buggy but worked for most bitmaps I tried to convert.

[//]: #
[AdafruitGFX]: https://github.com/adafruit/Adafruit-GFX-Library
[converter]: https://www.topwaydisplay.com/en/drivers-tools
