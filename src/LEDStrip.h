//
// Created by Kodiko Dytis on 09/05/16.
//

#ifndef FOOSBALLINO_LEDSTRIP_H
#define FOOSBALLINO_LEDSTRIP_H

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
#include <WProgram.h>
  #include <pins_arduino.h>
#endif

#include <Adafruit_NeoPixel.h>


enum  pattern {
    NONE,
    THEATER_CHASE,
    COLOR_WIPE,
    SCANNER,
    FADE
};

enum  direction {
    FORWARD,
    REVERSE
};


class LEDStrip {

public:
    LEDStrip(uint32_t, uint32_t);
    void goal_effect(byte team);
    void update();
    void set_default();
    void theater_chase(uint32_t, uint32_t, uint8_t, direction);
    void scanner(uint32_t, uint8_t, direction);
    void fade(uint32_t, uint32_t, uint16_t, uint8_t);


private:
    Adafruit_NeoPixel* strip;
    uint32_t LedCount;
    uint32_t LastUpdate;
    uint8_t Interval;
    uint32_t Color1;
    uint32_t Color2;
    uint32_t Color3;
    uint16_t TotalSteps;
    uint16_t Index;
    direction Direction;
    pattern Pattern;


    void increment();
    void theater_chase_update();
    void fade_update();
    void scanner_update();
    uint32_t dim_color(uint32_t);
};


#endif //FOOSBALLINO_LEDSTRIP_H
