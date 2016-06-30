#ifndef FOOSBALLINO_GOALDETECTOR_H
#define FOOSBALLINO_GOALDETECTOR_H

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif

#include "config.h"

class GoalDetector {

public:
    GoalDetector();
    GoalDetector(uint32_t);
    bool is_goal();
    void set_pin(uint32_t);

private:
    uint32_t pin;            // Pin for the sensor used by the detector
    uint32_t prev_goal_time; // Time of the last detected goal

    void init();
};

#endif //FOOSBALLINO_GOALDETECTOR_H
