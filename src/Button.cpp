//
// Created by Kodiko Dytis on 12/05/16.
//

#include "Button.h"

Button::Button() {
    this->pin = 0;
}

Button::Button(uint32_t pin) {
    this->set_pin(pin);
}

bool Button::is_pressed() {
    return digitalRead(pin) == HIGH;
}

void Button::set_pin(uint32_t pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}