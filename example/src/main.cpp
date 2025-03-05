// Config: Driver: SSD1322; MCU: ESP32-S3; Framework: Arduino


// arduino framework + esp32 spi
#include <Arduino.h>
#include <SPI.h>

// include the ssd1322 lib
#include <SSD1322.h>

// example images
#include <creeper.h>
#include <krecik.h>
#include <pat_i_mat.h>
#include <stars_4bpp.h>
#include <tom_and_jerry.h>

// adafruit fonts
#include <FreeMono12pt7b.h>
#include <FreeSansOblique9pt7b.h>

// SPI Pins
#define OLED_CLOCK 12
#define OLED_DATA 13
#define OLED_CS 10
#define OLED_DC 11
#define OLED_RESET -1 // no reset pin

// display size
#define OLED_WIDTH 256
#define OLED_HEIGHT 64

// buffer + display instance
uint8_t tx_buf[OLED_WIDTH * OLED_HEIGHT / 2];
SSD1322 display(OLED_CS, OLED_DC, OLED_RESET, OLED_HEIGHT, OLED_WIDTH);

// ### demo functions:

void clearDisplayBuffer()
{
  display.gfx.fill_buffer(tx_buf, 0);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
}

void drawBasicShapes()
{
  display.gfx.draw_pixel(tx_buf, 10, 10, 1);
  display.gfx.draw_pixel(tx_buf, 15, 15, 5);
  display.gfx.draw_pixel(tx_buf, 20, 20, 9);
  display.gfx.draw_pixel(tx_buf, 25, 25, 15);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(2000);

  display.gfx.draw_hline(tx_buf, 31, 20, 50, 10);
  display.gfx.draw_vline(tx_buf, 31, 0, 31, 10);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(2000);

  display.gfx.draw_line(tx_buf, 40, 0, 80, 31, 12);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(2000);

  display.gfx.draw_AA_line(tx_buf, 50, 0, 90, 31, 12);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(2000);

  display.gfx.draw_circle(tx_buf, 180, 20, 20, 15);
  display.gfx.draw_rect(tx_buf, 100, 5, 120, 25, 15);
  display.gfx.draw_rect_filled(tx_buf, 124, 5, 144, 25, 8);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(2000);
}

void displayBitmaps()
{
  display.gfx.draw_bitmap_8bpp(tx_buf, pat_i_mat, 0, 0, 64, 64);
  display.gfx.draw_bitmap_8bpp(tx_buf, krecik, 128, 0, 64, 64);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(5000);

  display.gfx.draw_bitmap_4bpp(tx_buf, stars_4bpp, 0, 0, 256, 64);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(3000);
}

void testDisplayModes()
{
  display.api.SSD1322_API_set_display_mode(SSD1322_MODE_INVERTED);
  delay(2000);
  display.api.SSD1322_API_set_display_mode(SSD1322_MODE_ON);
  delay(1000);
  display.api.SSD1322_API_set_display_mode(SSD1322_MODE_OFF);
  delay(1000);
  display.api.SSD1322_API_set_display_mode(SSD1322_MODE_NORMAL);
  delay(500);
}

void setCustomGrayscale()
{
  uint8_t grayscale_tab[16] = {0, 5, 10, 15, 20, 25, 30, 35, 145, 150, 155, 160, 165, 170, 175, 180};
  display.api.SSD1322_API_custom_grayscale(grayscale_tab);
  delay(2000);
  display.api.SSD1322_API_default_grayscale();
  delay(2000);
}

void testSleepMode()
{
  display.api.SSD1322_API_sleep_on();
  delay(1000);
  display.api.SSD1322_API_sleep_off();
}

void displayText()
{
  display.gfx.select_font(&FreeMono12pt7b);
  display.gfx.draw_text(tx_buf, "Lorem ipsum", 10, 20, 15);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(2000);

  display.gfx.select_font(&FreeSansOblique9pt7b);
  display.gfx.draw_text(tx_buf, "dolor sit amet", 10, 45, 15);
  display.gfx.send_buffer_to_OLED(tx_buf, 0, 0);
  delay(2000);
}

void displayLargeBitmap()
{
  uint8_t tx_buf2[256 * 256 / 2];
  display.gfx.set_buffer_size(256, 256);
  display.gfx.draw_bitmap_8bpp(tx_buf2, creeper, 0, 0, 256, 256);
  display.gfx.send_buffer_to_OLED(tx_buf2, 0, 0);
  delay(2000);

  for (int i = 0; i < 192; i++)
  {
    display.gfx.send_buffer_to_OLED(tx_buf2, 0, i);
    delay(5);
  }
  delay(200);
  for (int i = 191; i >= 0; i--)
  {
    display.gfx.send_buffer_to_OLED(tx_buf2, 0, i);
    delay(5);
  }
  delay(2000);
}

void setup()
{
  pinMode(OLED_CS, OUTPUT);
  pinMode(OLED_DC, OUTPUT);

  SPI.begin(OLED_CLOCK, -1, OLED_DATA, OLED_CS);
  delay(500);

  // init display
  display.api.SSD1322_API_init();

  // init buffer
  display.gfx.set_buffer_size(256, 64);
  clearDisplayBuffer();

  // shapes
  drawBasicShapes();
  clearDisplayBuffer();

  // bitmaps
  displayBitmaps();
  clearDisplayBuffer();

  // modes
  testDisplayModes();
  clearDisplayBuffer();

  // grayscale
  setCustomGrayscale();
  clearDisplayBuffer();

  // sleepmode
  testSleepMode();
  clearDisplayBuffer();

  // text
  displayText();
  clearDisplayBuffer();

  // large bitmap
  // displayLargeBitmap();
  // clearDisplayBuffer();
}

void loop()
{
}