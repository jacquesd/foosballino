/**
    Logic for the buttons used to control the system.
*/
#include "Button.h"

/**
    Create a new button with the default pin 0.
*/
Button::Button() {
    this->pin = 0;
    pressed = false;
}

/**
    Create a new button with the given pin.
*/
Button::Button(uint32_t pin) {
    this->set_pin(pin);
    pressed = false;
}

/**
    Indicate wether the button is currently pressed or not.

    Note that if the button is constantly pressed this will count as a single
    press and the function will return the button as unpressed until it is
    released and pressed again.

    @return `true` if pressed, `false` otherwise
*/
bool Button::is_pressed() {
    if (pressed) {
        if (digitalRead(pin) == LOW) {
            pressed = false;
        }
    } else {
        if (digitalRead(pin) == HIGH) {
            pressed = true;
        }
    }
    return pressed;
}

/**
    Set the pin to use for the button.

    This also sets the mode of the pin to `INPUT`.

    @param pin: The new pin to use for the button.
*/

void Button::set_pin(uint32_t pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}
