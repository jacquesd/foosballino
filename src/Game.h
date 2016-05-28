//
// Created by Kodiko Dytis on 06/05/16.
//

#ifndef FOOSBALLINO_GAME_H
#define FOOSBALLINO_GAME_H

#include <stdint.h>

#include "Button.h"
#include "GoalDetector.h"
#include "LEDStrip.h"

#define SCORE_LIMIT = 99
#define TEAM_A 0
#define TEAM_B 1
#define MINUS 0
#define PLUS 1
#define DEFAULT_MAX_SCORE 10
#define END_TIMEOUT 5000 // ms
#define LED_COUNT 70 //leds per strip


enum State {
    start_state,
    game_state,
    settings_state,
    end_state
};

class Game {

public:
    Game(uint32_t[2], uint32_t[4], uint32_t, uint32_t, uint32_t);
    void update();

private:
    State state;
    int max_scores[2];
    int scores[2];
    GoalDetector goals[2];
    Button* buttons[4];
    Button* reset_button;
    Button* settings_button;
    LEDStrip* led_strip;
    uint32_t end_time;

    void start_update();
    void game_update();
    void settings_update();
    void end_update();

    void reset_scores();
    void update_score(byte);
};


#endif //FOOSBALLINO_GAME_H
