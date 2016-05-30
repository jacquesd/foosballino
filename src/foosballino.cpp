#include <Arduino.h>
#include "Game.h"

Game* game;

// #include "time.h"
//
// int start;
// int dur;

void setup() {
    Serial.begin(9600);
    Serial.print("Game create\n");
    game = new Game(2);
    Serial.print("Game created\n");
    // start = millis();
}

void loop() {
   game->update();
   // dur  = (millis() - start) / 1000;
   // Serial.write(27);
   // Serial.print(String(minutes(dur)) + ":" + String(seconds(dur)) + "\n");
   // delay(500);
}
