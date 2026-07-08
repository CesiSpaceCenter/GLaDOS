#ifndef _RACER_SCREEN_H
#define _RACER_SCREEN_H

#include <bnp.h>
#include <Adafruit_SSD1306.h>

namespace racer::screen {
    extern Adafruit_SSD1306 display;

    void init();
    void draw_text(const char* text, int x, int y, int color, const GFXfont* font);
    void task(void* arg);
}

#endif