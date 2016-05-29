//
// Created by Kodiko Dytis on 12/05/16.
//

#ifndef FOOSBALLINO_BUTTON_H
#define FOOSBALLINO_BUTTON_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
  #include <pins_arduino.h>
#endif

#define BUTTON_INTERVAL 100

class Button {

public:
    Button();
    Button(uint32_t);
    bool is_pressed();
    void set_pin(uint32_t);

private:
    uint32_t pin;
    uint32_t last_read;
    bool pressed;
};


#endif //FOOSBALLINO_BUTTON_H
