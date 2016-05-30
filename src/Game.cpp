//
// Created by Kodiko Dytis on 06/05/16.
//

#include "Game.h"

Game::Game() {
    state = start_state;

    scores[TEAM_A] = 0;
    scores[TEAM_B] = 0;

    max_scores[TEAM_A] = DEFAULT_MAX_SCORE;
    max_scores[TEAM_A] = DEFAULT_MAX_SCORE;


    goals[TEAM_A].set_pin(A_GOAL_PIN);
    goals[TEAM_B].set_pin(B_GOAL_PIN);

    dec_buttons[TEAM_A].set_pin(A_DEC_PIN);
    inc_buttons[TEAM_A].set_pin(A_INC_PIN);
    dec_buttons[TEAM_B].set_pin(B_DEC_PIN);
    inc_buttons[TEAM_B].set_pin(B_INC_PIN);

    reset_button    = new Button(RESET_PIN);
    settings_button = new Button(SETTINGS_PIN);
    mode_button = new Button(MODE_PIN);

    timed_game = mode_button->is_pressed();
    duration = 600000; // 10 minutes;

    led_strip = new LEDStrip(LED_COUNT, LED_PIN);

    led_strip->fade(TEAM_B_ALT_COLOR, TEAM_A_COLOR, 200, 40);

    display = new Display();
    display->welcome();
}

void Game::update() {
    led_strip->update();
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
    timed_game = mode_button->is_pressed();
    if (settings_button->is_pressed()) {
        state = settings_state;
    } else if (reset_button->is_pressed()) {
        reset_scores();
        state = game_state;
        led_strip->flood_light();
        start_time = millis();
    }
}

void Game::settings_update() {
    timed_game = mode_button->is_pressed();

    if (timed_game) {
        display->duration_settings(duration);
        if (dec_buttons[TEAM_A].is_pressed()) {
            duration = (minutes(duration) <= 0)
                       ? (59 * MSECS_PER_MIN  + seconds(duration))
                       : (duration - MSECS_PER_MIN);
        }

        if (inc_buttons[TEAM_A].is_pressed()) {
            duration = (minutes(duration) >= 59)
                       ? seconds(duration)
                       : (duration + MSECS_PER_MIN);
        }

        if (dec_buttons[TEAM_B].is_pressed()) {
            duration = (seconds(duration) <= 0)
                       ? (minutes(duration) + 59 * MSECS_PER_SEC)
                       : (duration - MSECS_PER_SEC);
        }

        if (inc_buttons[TEAM_B].is_pressed()) {
            duration = (seconds(duration) >= 59)
                       ? minutes(duration)
                       : (duration + MSECS_PER_SEC);
        }
    } else {
        display->score_settings(max_scores);
        if (dec_buttons[TEAM_A].is_pressed()) {
            max_scores[TEAM_A] = (max_scores[TEAM_A] < 1) ? 99 : (max_scores[TEAM_A] - 1);
        }

        if (inc_buttons[TEAM_A].is_pressed()) {
            max_scores[TEAM_A] = (max_scores[TEAM_A] >= 99) ? 1 : (max_scores[TEAM_A] + 1);
        }

        if (dec_buttons[TEAM_B].is_pressed()) {
            max_scores[TEAM_B] = (max_scores[TEAM_B] < 1) ? 99 : (max_scores[TEAM_B] - 1);
        }

        if (inc_buttons[TEAM_B].is_pressed()) {
            max_scores[TEAM_B] = (max_scores[TEAM_B] >= 99) ? 1 : (max_scores[TEAM_B] + 1);
        }
    }

    if (settings_button->is_pressed()) {
        state = start_state;
    }
}

void Game::game_update() {

    update_score(TEAM_A);
    update_score(TEAM_B);
    display->scores(scores, duration);

    if (timed_game && millis() - start_time > duration) {
        state = end_state;
        end_time = millis();
        if (scores[TEAM_A] > scores[TEAM_B]) {
            led_strip->theater_chase(TEAM_A_ALT_COLOR, TEAM_A_COLOR, 200, FORWARD);

        }  else if (scores[TEAM_A] < scores[TEAM_B]) {
            led_strip->theater_chase(TEAM_B_ALT_COLOR, TEAM_B_COLOR, 200, REVERSE);

        } else {
            led_strip->theater_chase(TEAM_A_ALT_COLOR, TEAM_B_ALT_COLOR, 200, REVERSE);
        }
    } else if (scores[TEAM_A] >= max_scores[TEAM_A]) {
        state = end_state;
        end_time = millis();
        led_strip->theater_chase(TEAM_A_ALT_COLOR, TEAM_A_COLOR, 200, FORWARD);

    } else if (scores[TEAM_B] >= max_scores[TEAM_B]) {
        state = end_state;
        end_time = millis();
        led_strip->theater_chase(TEAM_B_COLOR, TEAM_B_ALT_COLOR, 200, REVERSE);
        led_strip->fade(TEAM_B_COLOR, TEAM_A_COLOR, 200, 40);
    }
}

void Game::end_update() {
    if (dec_buttons[TEAM_A].is_pressed()) {
        scores[TEAM_A]--;
        state = game_state;
        led_strip->set_default();

    } else if (dec_buttons[TEAM_B].is_pressed()) {
        scores[TEAM_B]--;
        state = game_state;
        led_strip->set_default();

    } else if (reset_button->is_pressed()) {
        reset_scores();
        state = game_state;
        led_strip->set_default();
        start_time = millis();

    } else if (millis() - end_time > END_TIMEOUT) {
        state = start_state;
        led_strip->fade(TEAM_B_COLOR, TEAM_A_COLOR, 200, 40);
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

    if (scores[team] > 0 && dec_buttons[team].is_pressed()) {
        scores[team]--;
        if (team == TEAM_A) {
            Serial.print("Minus A\n");
        } else {
            Serial.print("Minus B\n");
        }
    }

    if (/*goals[team]->isGoal() ||*/ inc_buttons[team].is_pressed()) {
        scores[team]++;
        if (team == TEAM_A) {
            led_strip->scanner(TEAM_A_COLOR, 20, FORWARD);
        } else {
            led_strip->scanner(TEAM_B_COLOR, 20, REVERSE);
        }

    }
}
