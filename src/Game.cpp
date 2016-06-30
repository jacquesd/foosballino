#include "Game.h"

/**
    Main game logic which sets up the buttons, LEDs, goal detectors and the
    screen according to the pin values specified in `config.h` and keep track
    of the scores.
*/
Game::Game() {
    DEBUG_PRINT("Scores:         ");
    scores[TEAM_A] = 0;
    scores[TEAM_B] = 0;

    max_scores[TEAM_A] = DEFAULT_MAX_SCORE;
    max_scores[TEAM_B] = DEFAULT_MAX_SCORE;
    DEBUG_PRINT("            [OK]\n");

    DEBUG_PRINT("Goal Detectors:");
    goals[TEAM_A].set_pin(A_GOAL_PIN);
    goals[TEAM_B].set_pin(B_GOAL_PIN);
    DEBUG_PRINT("    [OK]\n");

    DEBUG_PRINT("Buttons:");
    dec_buttons[TEAM_A].set_pin(A_DEC_PIN);
    inc_buttons[TEAM_A].set_pin(A_INC_PIN);
    dec_buttons[TEAM_B].set_pin(B_DEC_PIN);
    inc_buttons[TEAM_B].set_pin(B_INC_PIN);

    reset_button    = new Button(RESET_PIN);
    settings_button = new Button(SETTINGS_PIN);
    DEBUG_PRINT("           [OK]\n");

    DEBUG_PRINT("LED Strip:");
    led_strip = new LEDStrip(LED_COUNT, LED_DATA_PIN, LED_PWR_PIN);
    DEBUG_PRINT("         [OK]\n");

    DEBUG_PRINT("Display:");
    display   = new Display();
    DEBUG_PRINT("           [OK]\n");

    DEBUG_PRINT("State: ");
    to_start();
    DEBUG_PRINT("            [OK]\n");
}

/**
    Main update loop of the game.

    Update the LED strip and then triggers the update loop for the actual state
    of the game object.
*/
void Game::update() {
    led_strip->update();

    switch (state) {
        case START:
            start_update();
            break;
        case SETTINGS:
            settings_update();
            break;
        case GAME:
            game_update();
            break;
        case END:
            end_update();
            break;
    }
}

/**
    Transition function to change the state of the game to the "START" state.
*/
inline void Game::to_start() {
    DEBUG_PRINT("mode: START\n");
    state = START;
    led_strip->idle_effect();
    display->start();
}

/**
    Transition function to change the state of the game to the "END" state.
*/
inline void Game::to_game() {
    DEBUG_PRINT("mode: GAME\n");
    state = GAME;
    display->game(scores);
    led_strip->game_effect();
}

/**
    Transition function to change the state of the game to the "SETTINGS" state.
*/
inline void Game::to_settings() {
    DEBUG_PRINT("mode: SETTINGS\n");
    state = SETTINGS;
    led_strip->settings_effect();
    display->settings(max_scores);
}

/**
    Transition function to change the state of the game to the "END" state.
*/
inline void Game::to_end() {
    DEBUG_PRINT("mode: END\n");
    state = END;
    end_time = millis();
}

/**
    Update loop for the "START" state.

    Initial state of the system.
    In this state, the system can transition to the "SETTINGS" state to adjust
    the settings or to the "GAME" state to start a new game.
*/
void Game::start_update() {
    if (settings_button->is_pressed()) {
        to_settings();
    } else if (reset_game()) {
        to_game();
    }
}

/**
    Update loop for the "GAME" state.

    State of the system during a foosball game.
    In this state, the system keeps tracks of the score and detects goals using
    the goal detectors and the arcade buttons.
    The system can transition to the "START" state to end the game preemptively.
    Once a team reaches the maximum score, the system automatically moves to the
    "END" state.
*/
void Game::game_update() {
    update_score(TEAM_A);
    update_score(TEAM_B);

    if (wins(TEAM_A) || wins(TEAM_B)) {
        to_end();
    } else if (reset_button->is_pressed()) {
        to_start();
    }
}

/**
    Update loop for the "SETTINGS" state.

    State to configure the settings.
    In this state, the maximum number of goal or maximum score can be set
    independently for each team.
    The system can only move back to the "START" state from this state.
*/
void Game::settings_update() {
    update_max_score(TEAM_A);
    update_max_score(TEAM_B);

    if (settings_button->is_pressed()) {
        to_start();
    }
}

/**
    Update loop for the "END" state.

    State once a foosball game is over.
    In this state, the system indicate which team won. If the wining goal is
    invalid, it can be canceled; in this case the system will transition back to
    the "GAME" state with the old scores.
    The system can be moved to the "GAME" state using the "new game" button to
    start a new foosball game immediately.
    After a given delay (`END_TIMEOUT`) the system will automatically go the
    "START" state.
*/
void Game::end_update() {
    if (cancel_goal(TEAM_A) || cancel_goal(TEAM_B) || reset_game()) {
        to_game();

    } else if (millis() - end_time > END_TIMEOUT) {
        to_start();
    }
}

/**
    Update the maximum number of goals the given team can score.

    The maximum number of goals is used to determine when a game ends.
    The smallest value is 1 and the largest value is 99. The score is changed
    using buttons and updated on the screen directly.

    @param team: The team for which to update the score.
*/
inline void Game::update_max_score(int team) {
    bool dirty = false;
    if (dec_buttons[team].is_pressed()) {
        max_scores[team] = (max_scores[team] <= 1)
            ? 99
            : (max_scores[team] - 1);
        dirty = true;
    }
    if (inc_buttons[team].is_pressed()) {
        max_scores[team] = (max_scores[team] >= 99)
            ? 1
            : (max_scores[team] + 1);
        dirty = true;
    }

    if (dirty) {
        display->update_score(max_scores[team], team);
    }
}


/**
    Check the score to see wether the given team won the game.

    A victory is declared if the team's score reaches the maximum score the team
    can obtain.

    @param team: the team for which to check the score.
    @return `true` if the team won, `false` otherwise.
*/
bool Game::wins(int team) {
    if (scores[team] < max_scores[team]) {
        return false;
    }

    led_strip->victory_effect(team);
    display->end(team);
    return true;
}

/**
    Check and indicate that a winning goal is cancel if requested.

    If the given team has won (its score has reached the max. score) and the
    button to decrease the score has been pressed, the last goal is canceled,
    reducing the score by 1. If this is the case, the function returns `true`,
    otherwise it returns `false`

    @param team: the team for which to check the score and cancel the goal
    @return `true` if the goal has been canceled, `false` otherwise
*/
inline bool Game::cancel_goal(int team) {
    if (scores[team] >= max_scores[team] && dec_buttons[team].is_pressed()) {
        scores[team] = max_scores[team] - 1;
        return true;
    }
    return false;
}

/**
    Reset the scores of the current game if the reset button is pressed.

    @return `true` if the scores where reset, false otherwise
*/

inline bool Game::reset_game() {
    if (reset_button->is_pressed()) {
        scores[TEAM_A] = 0;
        scores[TEAM_B] = 0;
        return true;
    }
    return false;
}

/**
    Update the score of the given team.

    If a goal has been detected or manually added/removed using the buttons, the
    score of the team is update and the screen is update the reflect the change.
    In addition a light effect is triggered in the LED strips for a scored goal.
*/
void Game::update_score(int team) {
    if (scores[team] >= max_scores[team]) {
        return;
    }

    if (scores[team] > 0 && dec_buttons[team].is_pressed()) {
        scores[team]--;
        display->update_score(scores[team], team);
    }

    if (goals[team].is_goal() || inc_buttons[team].is_pressed()) {
        scores[team]++;
        display->update_score(scores[team], team);
        led_strip->goal_effect(team);
    }
}
