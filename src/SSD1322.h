#ifndef SSD1322_H
#define SSD1322_H

#include "SSD1322_API.h"
#include "SSD1322_GFX.h"
#include "SSD1322_HW_Driver.h"

// wrapper class of individual classes
class SSD1322
{
public:
    SSD1322(int OLED_CS_PIN, int OLED_DC_PIN, int OLED_HEIGHT_SIZE, int OLED_WIDTH_SIZE, int OLED_RESET_PIN = -1);

    // individual instances
    SSD1322_HW_DRIVER driver;
    SSD1322_API api;
    SSD1322_GFX gfx;
};

#endif /* SSD1322_H */