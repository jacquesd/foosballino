/**
    Logic for the PIR sensor used to detect a ball drop in the goal.
*/
#include "GoalDetector.h"

/**
    Create a new GoalDetector with the default pin 0.
*/
GoalDetector::GoalDetector() {
    pin = 0;
}


/**
    Create a new GoalDetector with the given pin value.
*/
void GoalDetector::set_pin(uint32_t pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
    init();
}

/**
    Initialize the goal detector.
*/
void GoalDetector::init() {
    prev_goal_time = millis();
}

/**
    Indicate whether a goal was detected.

    The logic includes bounce detection to avoid detecting the same goal twice,
    using an interval (GOAL_BOUNCE_DT). For this reason, there can be at most
    one goal every GOAL_BOUNCE_DT ms.
*/
bool GoalDetector::is_goal() {
    bool goal = digitalRead(pin) == HIGH;
    if (!goal) {
        return false;
    }

    uint32_t now = millis();
    if (now - prev_goal_time < GOAL_BOUNCE_DT) {
        goal = false;
    } else {
        prev_goal_time = now;
    }

    return goal;
}
