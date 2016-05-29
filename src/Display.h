//
// Created by Kodiko Dytis on 28/05/16.
//

#ifndef FOOSBALLINO_DISPLAY_H
#define FOOSBALLINO_DISPLAY_H

#include <SPI.h>
#include <TFT_22_ILI9225.h>
// #include <screen_4D_22_library.h>

#include "time.h"
#include "config.h"

#define TEAM_A 0
#define TEAM_B 1

class Display {
public:
   Display();
   void scores(uint16_t[2], uint32_t time);
   void welcome();
   void victory(uint8_t);
   void draw();
   void score_settings(uint16_t[2]);
   void duration_settings(uint32_t);
   void clear();
   bool refresh();

private:
   TFT_22_ILI9225* tft;
   uint32_t last_update;
};


#endif //FOOSBALLINO_DISPLAY_H
