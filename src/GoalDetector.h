//
// Created by Sammy Rosso on 14/05/16.
//

#ifndef FOOSBALLINO_GOALDETECTOR_H
#define FOOSBALLINO_GOALDETECTOR_H

#include <Arduino.h>

#define min_distance 5
#define bounce_interval 2000

class GoalDetector {

public:
    GoalDetector();
    GoalDetector(uint32_t);
    bool isGoal();
    void set_pin(uint32_t);

private:
    uint32_t pin;
    uint32_t prev_goal_time;
    uint32_t prev_goal_value;
    void init();
};

#endif //FOOSBALLINO_GOALDETECTOR_H
