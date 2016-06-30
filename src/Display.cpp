/*
    Logic for the display used to show the scores.

    Note: Pixel positions are hard coded as they are specific to a unique
    display model with a fixed resolution.
**/
#include "Display.h"

/**
    Instantiate a new display object with the pins specified in `/src/config.h`.

    Wrapper around the `tft` object provided by the display's library.
    Contains utility functions to display the scores and relevant information.
*/
Display::Display() {
   tft = new TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);
   tft->begin();
   tft->setOrientation(1);
   tft->setBacklight(HIGH);
}

/**
    Show the information related to the "START" state of the game.

    This shows instruction regarding which button to press to start a new game
    or access the settings menu.
*/
void Display::start() {
    tft->clear();
    logo();

    tft->setFont(Terminal12x16);
    tft->setBackgroundColor(COLOR_BLACK);

    tft->drawText(90, 18, "Start", COLOR_WHITE);
    tft->drawText(90, 80, "Settings");

    tft->fillCircle(52, 26, 18, COLOR_RED);
    tft->fillCircle(52, 88, 18, COLOR_BLUE);
}

/**
    Show the information related to the "SETTINGS" state of the game.

    This shows the maximum scores for each team and instructions on how to go
    back to the "START" state.
*/
void Display::settings(uint16_t scores[2]) {
    tft->clear();
    logo();

    tft->drawText(62, 2, "Settings");
    tft->drawText(93, 112, "exit");

    tft->fillCircle(79, 120, 6, COLOR_BLUE);

    update_score(scores[TEAM_A], TEAM_A);
    update_score(scores[TEAM_B], TEAM_B);
}

/**
    Show the information related to the "GAME" state of the game.

    This shows the current scores for each team and instructions on how to go
    back to the "START" state.
*/
void Display::game(uint16_t scores[2]) {
    tft->clear();
    logo();

    tft->drawText(93, 112, "exit");

    tft->fillCircle(79, 120, 6, COLOR_RED);

    update_score(scores[TEAM_A], TEAM_A);
    update_score(scores[TEAM_B], TEAM_B);
}

/**
    Update the score information on the display.

    This function does not clear the screen and should only be called after
    a function showing scores (`game()`, `settings()`) is initially called.
*/
void Display::update_score(uint16_t score, uint8_t team) {
    tft->setFont(Liberation_Sans27x36_Numbers);
    uint8_t offset = score < 10 ? 14 : 0;

    switch(team) {
        case TEAM_A:
            tft->fillRectangle(138, 30, 200, 92, COLOR_YELLOW);
            tft->setBackgroundColor(COLOR_YELLOW);
            tft->drawText(142 + offset, 40, String(score), COLOR_BLACK);
            break;
        case TEAM_B:
            tft->fillRectangle(20, 30, 82, 92, COLOR_SNOW);
            tft->setBackgroundColor(COLOR_SNOW);
            tft->drawText(24 + offset, 40, String(score), COLOR_BLACK);
            break;
    }
}

/**
    Show the information related to the "END" state of the game.

    This shows the which team is the victor and instructions on how to go
    start a new game.
*/
void Display::end(uint8_t team) {
   tft->clear();
   logo();

   tft->setFont(Terminal12x16);

   switch(team) {
        case TEAM_A:
            tft->setBackgroundColor(COLOR_BLACK);
            tft->drawText(74, 20, "Yellow", COLOR_YELLOW);
            tft->drawText(80, 70, "wins!", COLOR_YELLOW);
            break;
       case TEAM_B:
           tft->setBackgroundColor(COLOR_BLACK);
           tft->drawText(80, 20, "White", COLOR_SNOW);
           tft->drawText(80, 70, "wins!", COLOR_SNOW);
           break;
   }

   tft->drawText(93, 112, "start");
   tft->fillCircle(79, 120, 6, COLOR_RED);
}

/**
    Utility function to draw the USI and foosballino logo.
*/
void Display::logo() {
    tft->setFont(Terminal12x16);

    tft->fillRectangle(0, 137, 37, 175, COLOR_YELLOW);

    tft->setBackgroundColor(COLOR_YELLOW);
    tft->drawText(1, 138, "USI", COLOR_BLACK);
    tft->drawText(1, 155, "INF", COLOR_BLACK);

    tft->setBackgroundColor(COLOR_BLACK);
    tft->drawText(50, 147, "foosballino", COLOR_TURQUOISE);
}
