#include <Arduino.h>
#include "Game.h"

uint32_t button_pins[4] = {1, 2, 3, 4};
uint32_t reset_game_pin = 5;
uint32_t settings_pin = 5;
uint32_t mode_pin = 5;
uint32_t goal_pins[2] = {1, 2};
uint32_t led_pin = 6;

Game* game;

void setup() {
    //TODO set pins mode

    game = new Game(goal_pins, button_pins, reset_game_pin, settings_pin, mode_pin, led_pin);
}

void loop() {
    game->update();
}