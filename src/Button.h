//
// Created by Kodiko Dytis on 12/05/16.
//

#ifndef FOOSBALLINO_BUTTON_H
#define FOOSBALLINO_BUTTON_H

#include <Arduino.h>

class Button {

public:
    Button();
    Button(uint32_t);
    bool is_pressed();
    void set_pin(uint32_t);

private:
    uint32_t pin;
};


#endif //FOOSBALLINO_BUTTON_H
