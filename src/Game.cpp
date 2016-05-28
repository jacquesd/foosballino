//
// Created by Kodiko Dytis on 06/05/16.
//

#define MSECS_PER_SEC  (1000)
#define MSECS_PER_MIN  (60UL * 1000)
#define MSECS_PER_HOUR (3600UL * 1000)
#define MSECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for getting elapsed time */
#define seconds(_time_) (_time_ % MSECS_PER_MIN)
#define minutes(_time_) ((_time_ / MSECS_PER_MIN) % MSECS_PER_MIN)
#define hours(_time_) (( _time_% MSECS_PER_DAY) / MSECS_PER_HOUR)

#include "Game.h"

Game::Game(uint32_t goal_pins[2], uint32_t pins[4], uint32_t reset_game_pin, uint32_t settings_pin, uint32_t mode_pin,
           uint32_t led_pin) {
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
    mode_button = new Button(mode_pin);

    timed_game = mode_button->is_pressed();
    duration = 600000; // 10 minutes;

    led_strip = new LEDStrip(LED_COUNT, led_pin);
    led_strip->fade(0xff0000, 0x0000ff, 255, 40);
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
    timed_game = mode_button->is_pressed();
    if (settings_button->is_pressed()) {
        state = settings_state;
    } else if (reset_button->is_pressed()) {
        reset_scores();
        state = game_state;
        led_strip->set_default();
        start_time = millis();
    }
}

void Game::settings_update() {
    timed_game = mode_button->is_pressed();

    if (timed_game) {
        if (buttons[TEAM_A][MINUS].is_pressed()) {
            duration = (minutes(duration) <= 0)
                       ? (59 * MSECS_PER_MIN  + seconds(duration))
                       : (duration - MSECS_PER_MIN);
        }

        if (buttons[TEAM_A][PLUS].is_pressed()) {
            duration = (minutes(duration) >= 59)
                       ? seconds(duration)
                       : (duration + MSECS_PER_MIN);
        }

        if (buttons[TEAM_B][MINUS].is_pressed()) {
            duration = (seconds(duration) <= 0)
                       ? (minutes(duration) + 59 * MSECS_PER_SEC)
                       : (duration - MSECS_PER_SEC);
        }

        if (buttons[TEAM_B][PLUS].is_pressed()) {
            duration = (seconds(duration) >= 59)
                       ? minutes(duration)
                       : (duration + MSECS_PER_SEC);
        }
    } else {
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


    if (settings_button->is_pressed()) {
        state = start_state;
    }
}

void Game::game_update() {
    update_score(TEAM_A);
    update_score(TEAM_B);

    if (timed_game && millis() - start_time > duration) {
        state = end_state;
        end_time = millis();
        if (scores[TEAM_A] > scores[TEAM_B]) {
            led_strip->theater_chase(0xff0000, 0x00ff00, 40, FORWARD);
        }  else if (scores[TEAM_A] < scores[TEAM_B]) {
            led_strip->theater_chase(0x0000ff, 0x00ff00, 40, REVERSE);
        } else {
            led_strip->theater_chase(0x00ff00, 0xff00ff, 40, REVERSE);
        }
    } else if (scores[TEAM_A] >= max_scores[TEAM_A]) {
        state = end_state;
        end_time = millis();
        led_strip->theater_chase(0xff0000, 0x00ff00, 40, FORWARD);
    } else if (scores[TEAM_B] >= max_scores[TEAM_B]) {
        state = end_state;
        end_time = millis();
        led_strip->theater_chase(0x0000ff, 0x00ff00, 40, REVERSE);
    }
}

void Game::end_update() {
    if (buttons[TEAM_A][MINUS].is_pressed()) {
        scores[TEAM_A]--;
        state = game_state;
        led_strip->set_default();

    } else if (buttons[TEAM_B][MINUS].is_pressed()) {
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
        led_strip->fade(0xff0000, 0x0000ff, 255, 40);
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
        if (team == TEAM_A) {
            led_strip->scanner(0xff0000, 20, FORWARD);
        } else {
            led_strip->scanner(0x0000ff, 20, REVERSE);
        }

    }
}
