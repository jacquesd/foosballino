#ifndef FOOSBALLINO_GAME_H
#define FOOSBALLINO_GAME_H

#include <stdint.h>

#include "Button.h"
#include "config.h"
#include "LEDStrip.h"
#include "Display.h"
#include "GoalDetector.h"

/**
    All the possible states of the system.

    See the update function of each state for details.
*/
enum State {
    START,
    GAME,
    SETTINGS,
    END
};

class Game {

public:
    Game();
    void update();


private:
    State state;             // current state of the game
    uint16_t max_scores[2];  // maximum scores for each team
    uint16_t scores[2];      // current scores for each team
    GoalDetector goals[2];   // goal detectors for each team
    Button inc_buttons[2];   // increment button for each team's score
    Button dec_buttons[2];   // decrement button for each team's score
    Button* reset_button;    // button to reset or start a new game
    Button* settings_button; // button to access the settings menu
    LEDStrip* led_strip;     // LED strip of the foosball table
    Display* display;        // Display for the scores
    uint32_t end_time;       // Time at which the last game ended

    void to_start();
    void to_game();
    void to_settings();
    void to_end();

    void start_update();
    void game_update();
    void settings_update();
    void end_update();

    bool reset_game();
    void update_score(int);
    void update_max_score(int);
    bool wins(int);
    bool cancel_goal(int);
};

#endif //FOOSBALLINO_GAME_H
