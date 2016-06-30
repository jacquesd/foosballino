#ifndef FOOSBALLINO_BUTTON_H
#define FOOSBALLINO_BUTTON_H

#if (ARDUINO >= 100)
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif

class Button {

public:
    Button();
    Button(uint32_t);
    bool is_pressed();
    void set_pin(uint32_t);

private:
    uint32_t pin; // The pin from which to read the button's signal.
    bool pressed; // Internal state to keep track of whether the btn is pressed.
};

#endif //FOOSBALLINO_BUTTON_H
