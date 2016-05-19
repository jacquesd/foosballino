//
// Created by Kodiko Dytis on 06/05/16.
//

#include "Game.h"

Game::Game(uint32_t goal_pins[2], uint32_t pins[4], uint32_t reset_game_pin, uint32_t settings_pin) {
    state = start_state;

    scores[TEAM_A] = 0;
    scores[TEAM_B] = 0;

    max_scores[TEAM_A] = DEFAULT_MAX_SCORE;
    max_scores[TEAM_A] = DEFAULT_MAX_SCORE;


    goals[TEAM_A].set_pin(goal_pins[0]);
    goals[TEAM_B].set_pin(goal_pins[1]);

    buttons[TEAM_A][MINUS].set_pin(pins[0]);
    buttons[TEAM_A][PLUS].set_pin(pins[1]);
    buttons[TEAM_B][MINUS].set_pin(pins[2]);
    buttons[TEAM_B][PLUS].set_pin(pins[3]);

    reset_button    = new Button(reset_game_pin);
    settings_button = new Button(settings_pin);
}

void Game::update() {
    switch (state) {
        case start_state:
            start_update();
            break;
        case settings_state:
            settings_update();
            break;
        case game_state:
            game_update();
            break;
        case end_state:
            end_update();
            break;
    }
}

void Game::start_update() {
    if (settings_button->is_pressed()) {
        state = settings_state;
    } else if (reset_button->is_pressed()) {
        reset_scores();
        state = game_state;
    }
}

void Game::settings_update() {
    if (buttons[TEAM_A][MINUS].is_pressed()) {
        max_scores[TEAM_A] = (max_scores[TEAM_A] - 1 <= 1) ? 99 : (max_scores[TEAM_A] - 1);
    }

    if (buttons[TEAM_A][PLUS].is_pressed()) {
        max_scores[TEAM_A] = (max_scores[TEAM_A] + 1 >= 99) ? 1 : (max_scores[TEAM_A] + 1);
    }

    if (buttons[TEAM_B][MINUS].is_pressed()) {
        max_scores[TEAM_B] = (max_scores[TEAM_B] - 1 <= 1) ? 99 : (max_scores[TEAM_B] - 1);
    }

    if (buttons[TEAM_B][PLUS].is_pressed()) {
        max_scores[TEAM_B] = (max_scores[TEAM_B] + 1 <= 99) ? 1 : (max_scores[TEAM_B] + 1);
    }

    if (settings_button->is_pressed()) {
        state = start_state;
    }
}

void Game::game_update() {
    update_score(TEAM_A);
    update_score(TEAM_B);

    if (scores[TEAM_A] >= max_scores[TEAM_A] || scores[TEAM_B] >= max_scores[TEAM_B]) {
        state = end_state;
        end_time = millis();
    }
}

void Game::end_update() {
    if (buttons[TEAM_A][MINUS].is_pressed()) {
        scores[TEAM_A]--;
        state = game_state;

    } else if (buttons[TEAM_B][MINUS].is_pressed()) {
        scores[TEAM_B]--;
        state = game_state;

    } else if (reset_button->is_pressed()) {
        reset_scores();
        state = game_state;

    } else if (millis() - end_time > END_TIMEOUT) {
        state = start;
    }
}

void Game::reset_scores() {
    scores[TEAM_A]= 0;
    scores[TEAM_B] = 0;
}

void Game::update_score(byte team) {
    if (scores[team] >= max_scores[team]) {
        return;
    }

    if (scores[team] > 0 && buttons[team][MINUS].is_pressed()) {
        scores[team]--;
    }

    if (goals[team].isGoal() || buttons[team][PLUS].is_pressed()) {
        scores[team]++;
    }
}
