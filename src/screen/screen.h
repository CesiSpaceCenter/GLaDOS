#ifndef _RACER_SCREEN_H
#define _RACER_SCREEN_H

#include <bnp.h>
#include <Adafruit_SSD1306.h>
#include "../sensors/sensors.h"
#include "../optocom.h"
#include "racer_logo.h"
#include "fonts/FreeSansBoldOblique9pt7b.h"
#include "fonts/Petme8x8.h"

Adafruit_SSD1306 display(128, 64, bnp::i2c[2], -1);

void screen_init() {
    while(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) {
        Serial.println("error: could not initialize screen");
        bnp::sleep(5000);
    }
    display.clearDisplay();
    display.drawBitmap(0, 7, logo_racer, 128, 50, 1);
    display.display();
}

void draw_text(const char* text, int x, int y, int color = 1, const GFXfont* font = &Petme8x8) {
    display.setTextColor(color);
    display.setTextWrap(false);
    display.setFont(font);
    display.setCursor(x, y);
    display.print(text);
}

void screen_task(void* arg) {
    UNUSED(arg);
    bnp::sleep(1000);
    char buf[10];

    while (true) {
        display.clearDisplay();
        draw_text("R A C E R", 22, 12, 1, &FreeSansBoldOblique9pt7b);

        display.fillRect(28, 16, 32, 11, 1);
        draw_text("VBAT", 29, 26, 0);
        display.drawRect(59, 16, 42, 11, 1);
        sprintf(buf, "%.1fv", voltage);
        draw_text(buf, 60, 26, 1);

        display.fillRect(28, 28, 32, 11, 1);
        draw_text("IBAT", 29, 38, 0);
        display.drawRect(59, 28, 42, 11, 1);
        draw_text("1.6 A", 60, 38, 1);

        display.fillRect(28, 40, 32, 11, 1);
        draw_text("TEMP", 29, 50, 0);
        display.drawRect(59, 40, 42, 11, 1);
        sprintf(buf, "%.1f C", bar_data.temperature);
        draw_text(buf, 60, 50, 1);

        display.fillRect(28, 52, 32, 11, 1);
        draw_text("SCU", 29, 62, 0);
        display.drawRect(59, 52, 42, 11, 1);
        String state_text = "";
        switch (scu_state) {
            case BOOTING:
                state_text = "BOOT";
                break;
            case STANDBY:
                state_text = "STDBY";
                break;
            case ARMED:
                state_text = "ARMED";
                break;
            case ASCENT:
                state_text = "ASCNT";
                break;
            case DESCENT:
                state_text = "DESCT";
                break;
        }
        draw_text(state_text.c_str(), 60, 62, 1);

        display.display();
        bnp::sleep(2000);
    }
}

#endif