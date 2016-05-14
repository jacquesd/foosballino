//
// Created by Kodiko Dytis on 06/05/16.
//

#include "Game.h"

Game::Game(uint32_t pins[4], uint32_t reset_game_pin, uint32_t settings_pin) {
    this->scores[TEAM_A] = 0;
    this->scores[TEAM_B] = 0;

    this->max_scores[TEAM_A] = DEFAULT_MAX_SCORE;
    this->max_scores[TEAM_A] = DEFAULT_MAX_SCORE;

    this->in_game = true;

    buttons[TEAM_A][MINUS].set_pin(pins[0]);
    buttons[TEAM_A][PLUS].set_pin(pins[1]);
    buttons[TEAM_B][MINUS].set_pin(pins[2]);
    buttons[TEAM_B][PLUS].set_pin(pins[3]);

    this->reset_button    = new Button(reset_game_pin);
    this->settings_button = new Button(settings_pin);
}

void Game::update() {

    if (!in_game && settings_button->is_pressed()) {
        settings_mode = !settings_mode;
    }

    if (in_game && reset_button->is_pressed()) {
        reset_scores();
    }

    if (settings_mode) {
        settings_update();
        return;
    }

    if (in_game) {
        game_update();
    }

    if (scores[TEAM_A] >= max_scores[TEAM_A]) {
        reset_scores();
    } else if (scores[TEAM_B] >= max_scores[TEAM_B]) {
        reset_scores();
    }
}

void Game::game_update() {
    if (buttons[TEAM_A][MINUS].is_pressed() && scores[TEAM_A] > 0) {
        scores[TEAM_A]--;
    }

    if (buttons[TEAM_A][PLUS].is_pressed() && scores[TEAM_A] < max_scores[TEAM_A]) {
        scores[TEAM_A]++;
    }

    if (buttons[TEAM_B][MINUS].is_pressed() && scores[TEAM_B] > 0) {
        scores[TEAM_B]--;
    }

    if (buttons[TEAM_B][PLUS].is_pressed() && scores[TEAM_B] < max_scores[TEAM_B]) {
        scores[TEAM_B]++;
    }

    // Insert Goal detectors code here

    if (scores[TEAM_A] >= max_scores[TEAM_A]) {
        // victory
    } else if (scores[TEAM_B] >= max_scores[TEAM_B]) {
        // victory
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
}

void Game::reset_scores() {
    scores[TEAM_A]= 0;
    scores[TEAM_B] = 0;
}
