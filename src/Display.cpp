//
// Created by Kodiko Dytis on 28/05/16.
//

#include "Display.h"


Display::Display() {
   tft = new TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);
   tft->begin();
   tft->setOrientation(1);
   tft->setBacklight(HIGH);
   tft->clear();
   tft->setFont(Terminal12x16);
   last_update = millis();
}

bool Display::refresh() {
    uint32_t now = millis();
    if (now - last_update < 1000) {
        return false;
    }
    last_update = now;
    return true;
}


void Display::scores(uint16_t scores[2], uint32_t time) {
    if (! refresh()) {
        return;
    }
   // tft->setFont(Liberation_Sans27x36_Numbers);
   tft->drawText(10, 10, String(scores[TEAM_A]) + " - " + String(scores[TEAM_B]));
   tft->drawText(10, tft->maxY() - 30, String(minutes(time)) + ":" + String(seconds(time)));
}

void Display::clear() {
    tft->clear();
}

void Display::welcome() {
    tft->drawText(70, 30, "Press");
    tft->fillCircle(110, 80, 30, COLOR_RED);
    tft->drawText(40, 130, "to start");
}

void Display::victory(uint8_t team) {
   tft->clear();
   // tft->setFont(Liberation_Sans27x36_Numbers);
   if (team == 0) {
       tft->drawText(10, 10, "Yellow wins!");
   } else {
       tft->drawText(10, 10, "White wins!");
   }
}

void Display::draw() {
   // tft->clear();
   // tft->setFont(Liberation_Sans27x36_Numbers);
   // tft->drawText(10, 10, "Draw!");
}

void Display::score_settings(uint16_t scores[2]) {
   if (! refresh()) {
       return;
   }
   // tft->setFont(Liberation_Sans27x36_Numbers);
   tft->drawText(10, 10, String(scores[TEAM_A]) + " - " + String(scores[TEAM_B]));
}

void Display::duration_settings(uint32_t duration) {
   // tft->clear();
   // tft->setFont(Liberation_Sans27x36_Numbers);
   // tft->drawText(10, 10, String(minutes(duration)) + ":" + String(seconds(duration)));
}
