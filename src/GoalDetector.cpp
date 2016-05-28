//
// Created by Sammy Rosso on 14/05/16.
//

#include "GoalDetector.h"

GoalDetector::GoalDetector() {
    pin = 0;
}

void GoalDetector::set_pin(uint32_t pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
    init();
}

void GoalDetector::init() {
    prev_goal_time = millis();
    prev_goal_value = analogRead(pin);
}

bool GoalDetector::isGoal() {
    bool result = false;
    uint32_t curr_goal_value = analogRead(pin);
    if (prev_goal_value - curr_goal_value > min_distance) {
        uint32_t now = millis();
        if (now - prev_goal_time > bounce_interval) {
            result = true;
        }
        prev_goal_time = now;
    }
    prev_goal_value = curr_goal_value;
    return result;
}

