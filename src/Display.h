#ifndef FOOSBALLINO_DISPLAY_H
#define FOOSBALLINO_DISPLAY_H

#include <SPI.h>
#include <TFT_22_ILI9225.h>

#include "config.h"

class Display {
public:
   Display();
   void start();
   void settings(uint16_t[2]);
   void game(uint16_t[2]);
   void update_score(uint16_t, uint8_t);
   void update_time(uint32_t);
   void end(uint8_t);

private:
   TFT_22_ILI9225* tft;  // Reference to the actual display
   void logo();
};

#endif //FOOSBALLINO_DISPLAY_H
