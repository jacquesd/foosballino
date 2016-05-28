//
// Created by Kodiko Dytis on 28/05/16.
//

#include "Display.h"


Display::Display() {
    tft = new TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);
    tft->begin();
    Serial.begin(9600);
}


void Display::scores(uint16_t scores[2], uint32_t time) {
    tft->clear();
    tft->setFont(Trebuchet_MS16x21);
    tft->drawText(10, 10, String(scores[TEAM_A]) + " - " + String(scores[TEAM_B]));
    tft->drawText(10, tft->maxY() - 30, String(minutes(time)) + ":" + String(seconds(time)));
}

void Display::welcome() {
    tft->clear();
    tft->setFont(Trebuchet_MS16x21);
    tft->drawText(10, 10, "Welcome!");
}

void Display::victory(uint8_t team) {
    tft->clear();
    tft->setFont(Trebuchet_MS16x21);
    if (team == 0) {
        tft->drawText(10, 10, "Yellow wins!");
    } else {
        tft->drawText(10, 10, "White wins!");
    }
}

void Display::draw() {
    tft->clear();
    tft->setFont(Trebuchet_MS16x21);
    tft->drawText(10, 10, "Draw!");
}

void Display::score_settings(uint16_t scores[2]) {
    tft->clear();
    tft->setFont(Trebuchet_MS16x21);
    tft->drawText(10, 10, String(scores[TEAM_A]) + " - " + String(scores[TEAM_B]));
}

void Display::duration_settings(uint32_t duration) {
    tft->clear();
    tft->setFont(Trebuchet_MS16x21);
    tft->drawText(10, 10, String(minutes(duration)) + ":" + String(seconds(duration)));
}