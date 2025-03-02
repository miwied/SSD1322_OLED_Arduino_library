#include "SSD1322.h"

//====================== Constructor ========================//
SSD1322::SSD1322(int OLED_CS_PIN, int OLED_DC_PIN, int OLED_HEIGHT_SIZE, int OLED_WIDTH_SIZE, int OLED_RESET_PIN) : driver(OLED_CS_PIN, OLED_DC_PIN, OLED_RESET_PIN), api(&driver), gfx(&api, OLED_HEIGHT_SIZE, OLED_WIDTH_SIZE) {}