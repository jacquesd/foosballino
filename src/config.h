/**
    Configuration of the system

    Edit this file to change various settings such as the pin numbers for
    buttons, detectors and so
*/

#ifndef FOOSBALLINO_CONFIG_H
#define FOOSBALLINO_CONFIG_H

// The default number of maximum goals for both teams
#define DEFAULT_MAX_SCORE 10 // goals

// The delay during which to stay in the "END" state after a victory before
// transitioning to the "START" state; in ms.
#define END_TIMEOUT 10000 // ms

// Colors used by the teams
#define TEAM_A_COLOR 0xFFFF00
#define TEAM_A_ALT_COLOR 0x00ff00
#define TEAM_B_COLOR 0x0BB5FF
#define TEAM_B_ALT_COLOR 0x0000ff
#define TEAM_B_DISPLAY_COLOR

// Goal detectors
// Pins
#define A_GOAL_PIN 3
#define B_GOAL_PIN 2
// Delay between two goals in ms.
// Detections within this value will be considered as the same goal
#define GOAL_BOUNCE_DT 5000 // ms

// Led strip
// The number of individual LEDs on the strip.
#define LED_COUNT 70 // LEDs
// Data pin
#define LED_DATA_PIN 4
// Pin for the power switch used by the LEDs
#define LED_PWR_PIN 36

// Button pins
// Button to decrement Team A's score
#define A_DEC_PIN 30
// Button to increment Team A's score
#define A_INC_PIN 32
// Button to decrement Team B's score
#define B_DEC_PIN 31
// Button to increment Team B's score
#define B_INC_PIN 33
// Button to reset or start a new game
#define RESET_PIN 34
// Button to access the settings menu
#define SETTINGS_PIN 35

// Display pins
// Only hardware SPI is used, so MISO, MOSI and CLK pins are not specified.
#define TFT_RST 9
#define TFT_RS  8
#define TFT_CS  10  // SS
#define TFT_LED 7   // 0 if wired to +5V directly (= disabled)

// Debug mode
//#define DEBUG 1 // uncomment to print debug info over serial

// Do not modify below this line
//------------------------------------------------------------------------------

/**
    List of both temas, used for clarity in the code.
*/
enum Team {
    TEAM_A,
    TEAM_B
};
typedef Team Team;

// Debug print statment macro.
#ifdef DEBUG
    #define DEBUG_PRINT(x) Serial.print(x)
#else
    #define DEBUG_PRINT(x)
#endif

#endif //FOOSBALLINO_CONFIG_H
