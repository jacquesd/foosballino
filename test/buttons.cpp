/**
    Test sketch to check the mapping of the buttons.
*/
#include <Arduino.h>

#include "Button.h"
#include "config.h"

Button inc_buttons[2];
Button dec_buttons[2];

Button* reset_button;
Button* settings_button;
Button* mode_button;

void setup() {
    Serial.begin(9600);
    Serial.print("Game create\n");
    dec_buttons[TEAM_A].set_pin(A_DEC_PIN);
    inc_buttons[TEAM_A].set_pin(A_INC_PIN);
    dec_buttons[TEAM_B].set_pin(B_DEC_PIN);
    inc_buttons[TEAM_B].set_pin(B_INC_PIN);

    reset_button    = new Button(RESET_PIN);
    settings_button = new Button(SETTINGS_PIN);
    mode_button     = new Button(MODE_PIN);

    Serial.print("Game created\n");
}

void loop() {
   // game->update();
   if (dec_buttons[TEAM_A].is_pressed()) {
       Serial.print("A -\n");
   }
   if (inc_buttons[TEAM_A].is_pressed()) {
       Serial.print("A +\n");
   }
   if (dec_buttons[TEAM_B].is_pressed()) {
       Serial.print("B -\n");
   }
   if (inc_buttons[TEAM_B].is_pressed()) {
       Serial.print("B +\n");
   }
   if (reset_button->is_pressed()) {
       Serial.print("Reset\n");
   }
   if (settings_button->is_pressed()) {
       Serial.print("Setting\n");
   }
   if (mode_button->is_pressed()) {
       Serial.print("LED power\n");
   }
}
