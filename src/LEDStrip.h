//
// Created by Kodiko Dytis on 09/05/16.
//

#ifndef FOOSBALLINO_LEDSTRIP_H
#define FOOSBALLINO_LEDSTRIP_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

enum  Pattern {
    NONE,
    THEATER_CHASE,
    COLOR_WIPE,
    SCANNER,
    FADE
};

enum  Direction {
    FORWARD,
    REVERSE
};


class LEDStrip {

public:
    LEDStrip(uint32_t, uint32_t);
    void goal_effect(byte team);
    void update();
    void set_default();
    void theater_chase(uint32_t, uint32_t, uint8_t, Direction);
    void scanner(uint32_t, uint8_t, Direction);
    void fade(uint32_t, uint32_t, uint16_t, uint8_t);


private:
    Adafruit_NeoPixel* strip;
    uint32_t led_count;
    uint32_t last_update;
    uint8_t interval;
    uint32_t color1;
    uint32_t color2;
    uint16_t total_steps;
    uint16_t index;
    Direction direction;
    Pattern pattern;


    void increment();
    void theater_chase_update();
    void fade_update();
    void scanner_update();
    uint32_t dim_color(uint32_t);
};


#endif //FOOSBALLINO_LEDSTRIP_H
