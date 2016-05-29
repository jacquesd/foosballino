//
// Created by Kodiko Dytis on 12/05/16.
//

#include "Button.h"

Button::Button() {
    this->pin = 0;
    pressed = false;
}

Button::Button(uint32_t pin) {
    this->set_pin(pin);
    pressed = false;
}

bool Button::is_pressed() {
    uint32_t now = millis();
    if (now - last_read < BUTTON_INTERVAL) {
        return false;
    }
    last_read = now;
    if (pressed) {
        if (digitalRead(pin) == LOW) {
            pressed = false;
        }
        return false;
    } else {
        if (digitalRead(pin) == HIGH) {
            pressed = true;
        }
        return pressed;
    }
}

void Button::set_pin(uint32_t pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}
