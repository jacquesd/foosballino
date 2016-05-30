//
// Created by Kodiko Dytis on 28/05/16.
//

#ifndef FOOSBALLINO_CONFIG_H
#define FOOSBALLINO_CONFIG_H

// TEAMS (do not change)
#define TEAM_A 0
#define TEAM_B 1
#define TEAM_A_COLOR 0xffff00
#define TEAM_A_ALT_COLOR 0x00ff00
#define TEAM_B_COLOR 0xff00ff
#define TEAM_B_ALT_COLOR 0x0000ff

// Goal detector pins
#define A_GOAL_PIN 1
#define B_GOAL_PIN 1

// Led strip data pin
#define LED_PIN 4

// Button pins
#define A_DEC_PIN 30
#define A_INC_PIN 32
#define B_DEC_PIN 31
#define B_INC_PIN 33
#define RESET_PIN 34
#define SETTINGS_PIN 35
#define MODE_PIN 36

#define TFT_RST 9
#define TFT_RS  8
#define TFT_CS  10  // SS
#define TFT_LED 7   // 0 if wired to +5V directly


#endif //FOOSBALLINO_CONFIG_H
