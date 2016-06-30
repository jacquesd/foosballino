#ifndef FOOSBALLINO_LEDSTRIP_H
#define FOOSBALLINO_LEDSTRIP_H

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif

#include <Adafruit_NeoPixel.h>

#include "config.h"

/**
    List of all possible light patterns.
*/
enum  Pattern {
    FLOOD,
    THEATER_CHASE,
    COLOR_WIPE,
    FADE
};

/**
    Direction in which the current pattern should propagate.
*/
enum  Direction {
    FORWARD,
    REVERSE
};

class LEDStrip {

public:
    LEDStrip(uint32_t, uint32_t, uint32_t);
    void update();
    void game_effect();
    void goal_effect(int);
    void idle_effect();
    void settings_effect();
    void victory_effect(int);

private:
    Adafruit_NeoPixel* strip; // Reference to te actual LED strip
    Pattern pattern;          // Current pattern being displayed
    Direction direction;      // Direction of propagation of the pattern
    uint32_t led_count;       // Number of LEDS on the strip.
    uint32_t pwr_pin;         // Pin for the power switch
    uint32_t last_update;     // Time when the LEDs where last updated
    uint16_t interval;        // Interval of time needed between 2 updates
    uint32_t color1;          // Color used by the current pattern
    uint32_t color2;          // Color used by the current pattern
    uint32_t color3;          // Color used by the current pattern
    uint16_t total_steps;     // Max. number of steps in the current pattern
    uint16_t index;           // Current step fo the pattern.
    bool enabled;             // Whether the strip is on or off

    void off();
    void on();
    void increment();
    void flood(uint32_t, uint32_t, uint32_t, uint16_t, uint16_t);
    void flood_update();
    void color_wipe(uint32_t, uint32_t, uint16_t, Direction);
    void color_wipe_update();
    void theater_chase(uint32_t, uint32_t, uint16_t, Direction);
    void theater_chase_update();
    void fade(uint32_t, uint32_t, uint16_t, uint16_t);
    void fade_update();
};

#endif //FOOSBALLINO_LEDSTRIP_H
