/**
    Main file of the foosballino project.

    For configuration,  see `/src/config.h`.
*/

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif
#include "Game.h"

Game* game;  // main game object

void setup() {
    DEBUG_PRINT("Foosballino setup...\n");
    // Initialize Serial for the display's SPI and debug prints
    Serial.begin(9600);
    game = new Game();
    DEBUG_PRINT("Ready\n");
}

void loop() {
   game->update();
}
