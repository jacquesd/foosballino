#include <Arduino.h>
#include "Game.h"

uint32_t button_pins[4] = {1, 2, 3, 4};
uint32_t reset_game_pin = 5;
uint32_t settings_pin = 5;

Game* game;

void setup() {
    game = new Game(button_pins, reset_game_pin, settings_pin);
}

void loop() {
    game->update();
}