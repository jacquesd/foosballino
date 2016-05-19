//
// Created by Kodiko Dytis on 06/05/16.
//

#ifndef FOOSBALLINO_GAME_H
#define FOOSBALLINO_GAME_H

#include <stdint.h>

#include "Button.h"
#include "GoalDetector.h"

#define SCORE_LIMIT = 99
#define TEAM_A 0
#define TEAM_B 1
#define MINUS 0
#define PLUS 1
#define DEFAULT_MAX_SCORE 10


class Game {

public:
    Game(uint32_t[2], uint32_t[4], uint32_t, uint32_t);
    void update();

private:
    int max_scores[2];
    int scores[2];
    GoalDetector goals[2];
    Button* buttons[4];
    Button* reset_button;
    Button* settings_button;
    bool in_game;
    bool settings_mode;

    void settings_update();
    void game_update();
    void reset_scores();
    void update_score(byte);
};


#endif //FOOSBALLINO_GAME_H
