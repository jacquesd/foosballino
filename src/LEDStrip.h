//
// Created by Kodiko Dytis on 09/05/16.
//

#ifndef FOOSBALLINO_LEDSTRIP_H
#define FOOSBALLINO_LEDSTRIP_H

#include <Adafruit_NeoPixel.h>

#define LEFT 0
#define RIGHT 1

#define RED 128  // This is a random value




class LEDStrip {

public:
    LEDStrip(uint32_t, uint32_t, uint32_t);
    void goal_effect(byte team);


private:
    Adafruit_NeoPixel* strips[2];
    uint32_t led_count;

    void theater_chase(uint32_t, uint8_t);
};


#endif //FOOSBALLINO_LEDSTRIP_H
