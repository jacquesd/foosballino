#include "LEDStrip.h"

// Returns the Red component of a 32-bit color
#define Red(_color_) ((_color_ >> 16) & 0xFF)
// Returns the Green component of a 32-bit color
#define Green(_color_) ((_color_ >> 8) & 0xFF)
// Returns the Blue component of a 32-bit color
#define Blue(_color_) (_color_ & 0xFF)

/**
    Wrapper class around for an Adafruit Neopixel LED strip.

    Contains extra functionalities and light effects and patterns needed for the
    project. Patterns inspired by the official Adafruit documentation.

    Note that physically the foosball table has 2 LED Strips but they are both
    connected to the same data input and therefore act as one. Bot strips must
    have the same length.

    @param led_count: Number of LEDs on the strip.
    @param data_pin: Pin for the data input of the strip.
    @param pwr_pin: Pin for the switch used to turn the strip on or off.
*/
LEDStrip::LEDStrip(uint32_t led_count, uint32_t data_pin, uint32_t pwr_pin) {
    this->led_count = led_count;
    this->pwr_pin = pwr_pin;
    pinMode(this->pwr_pin, INPUT);

    // NEO_GRB    Pixels are wired for GRB bitstream, correct for neopixel stick
    // NEO_KHZ800 800 KHz bitstream (e.g. High Density LED strip), correct for
    //            neopixel stick
    strip = new Adafruit_NeoPixel(this->led_count, data_pin,
                                  NEO_GRB + NEO_KHZ800);

    strip->begin();
    strip->show(); // Initialize all pixels
    off();         // Turn off the strip

    last_update = millis();
}

/**
    Main update loop of the LED Strip.

    Update the progress of the current light effect and turn the strip on or off
    if needed.

    This function only performs an actual update at given intervals specified by
    the current light pattern.

    The actual update logic is specific to each pattern and is called based on
    the currently selected pattern.
*/
void LEDStrip::update() {

    if (digitalRead(pwr_pin) == LOW) {
        if (enabled) {
            off();
        }
        return;
    } else if (!enabled) {
        on();
    }

    uint32_t now = millis();
    if (!enabled || now - last_update < interval) {
        return;
    }
    last_update = now;

    switch (pattern) {
        case FLOOD:
            flood_update();
            break;
        case THEATER_CHASE:
            theater_chase_update();
            break;
        case COLOR_WIPE:
            color_wipe_update();
            break;
        case FADE:
            fade_update();
            break;
    }

    strip->show();
    increment();
}

/**
    Turn off the LED strip (explicitly)
*/
void LEDStrip::off() {
    enabled = false;
    for (uint32_t i=0; i < led_count; i++) {
        strip->setPixelColor(i, 0x000000);
    }
    strip->show();
}

/**
    Turn on the LED strip.

    This function will not explicitly turn on the strip. It only allows the
    update logic of the current pattern to be called on the next call to the
    main update function. The update logic of the light pattern is in charge of
    turning on the appropriate LEDs on the strip.
*/
void LEDStrip::on() {
    enabled = true;
}

/**
    Increment the current step (progress) of the current light effect.

    The current step rolls over after the last step is reached.
*/
void LEDStrip::increment() {
    bool update_pattern = false;
    switch (direction) {
        case FORWARD:
            index++;
            if (index > total_steps) {
                index = 0;
                update_pattern = true;
            }
            break;
        case REVERSE:
            index--;
            if (index < 0) {
                index = total_steps - 1;
                update_pattern = true;
            }
            break;
    }
    if (update_pattern) {
        switch (pattern) {
            case COLOR_WIPE:   // Color wipe happens when a goal is scored.
                game_effect(); // After the goal, the leds should go back to
                break;         // their game light pattern.
                               // This is a hack but implementing a  transition
                               // system for a single transistion would be an
                               // over complication.
            case FADE: // Fade the colors back in a continuous cycle;
                fade(color2, color3, total_steps, interval);
                break;
            default:   // Other patterns do not need an explicit update and can
                break; // cycle again once over.
        }
    }
}

/**
    Effect when the game is idling (START state of the game).
*/
void LEDStrip::idle_effect() {
    fade(TEAM_B_COLOR, TEAM_A_COLOR, 400, 20);
}

/**
    Effect when the game is SETTINGS state.
*/
void LEDStrip::settings_effect() {
    fade(0x0BB5FF, 0x0000FF, 100, 20);
}

/**
    Effect when the game is GAME state.
*/
void LEDStrip::game_effect() {
    flood(0xFFFFFF, 0x202020, 0x707070, 200, 1000);
}

/**
    Effect when a goal is scored.
*/
void LEDStrip::goal_effect(int team) {
    switch (team) {
        case TEAM_A:
            color_wipe(TEAM_A_COLOR, 0x707070, 20, REVERSE);
            break;
        case TEAM_B:
            color_wipe(TEAM_B_COLOR, 0x707070, 20, FORWARD);
            break;
    }
}

/**
    Effect when a team wins (END state).
*/
void LEDStrip::victory_effect(int team) {
    switch(team) {
        case TEAM_A:
            theater_chase(TEAM_A_ALT_COLOR, TEAM_A_COLOR, 100, FORWARD);
            break;
        case TEAM_B:
            theater_chase(TEAM_B_COLOR, TEAM_B_ALT_COLOR, 100, REVERSE);
            break;
    }
}

/**
    Flood light pattern which alternates between all LEDs at color3 and
    every other LEAD at color1 or color2.

    In practice used with different intensities of white lights for a slight
    twinkling effect which is more lively than plain flood lights.
*/
inline void LEDStrip::flood(uint32_t color1, uint32_t color2, uint32_t color3,
        uint16_t steps, uint16_t interval) {
    this->pattern = FLOOD;
    this->color1 = color1;
    this->color2 = color2;
    this->color3 = color3;
    this->total_steps = steps;
    this->interval = interval;
}

/**
    Logic to update the flood light pattern.
*/
void LEDStrip::flood_update() {
    if (index % 4 == 0) {
        for (uint32_t i=0; i < led_count - 1; i=i+2) {
            strip->setPixelColor(i, color1);
            strip->setPixelColor(i + 1, color2);
        }
    } else if (index % 4 == 1 || index % 4 == 3){
        for (uint32_t i=0; i < led_count; i++) {
            strip->setPixelColor(i, color3);
        }
    }
}

/**
    Wipe color1 along the strip. After the wipe has passed, LEDS are set to
    color2.
*/
inline void LEDStrip::color_wipe(uint32_t color1, uint32_t color2,
        uint16_t interval, Direction direction) {
    this->pattern = COLOR_WIPE;
    this->total_steps = led_count * 2;
    this->color1 = color1;
    this->color2 = color2;
    this->interval = interval;
    this->direction = direction;
    this->index = direction == FORWARD ? 0 : total_steps;
}

/**
    Logic to update the color wipe pattern.
*/
void LEDStrip::color_wipe_update() {
    switch (direction) {
        case FORWARD:
            if (index < led_count) {
                strip->setPixelColor(index, color1);
            } else {
                strip->setPixelColor(index - led_count, color2);
            }
            break;
        case REVERSE:
            if (index < led_count) {
                strip->setPixelColor(index, color2);
            } else {
                strip->setPixelColor(index - led_count, color1);
            }
            break;
    }
}

/**
    Traditional theater style chase of 2 colors along the strip.
*/
inline void LEDStrip::theater_chase(uint32_t color1, uint32_t color2,
        uint16_t interval, Direction direction) {
    this->pattern = THEATER_CHASE;
    this->index = 0;
    this->total_steps = led_count;
    this->interval = 100;
    this->color1 = color1;
    this->color2 = color2;
    this->direction = direction;
}

/**
    Logic to update the theater chase pattern.
*/
void LEDStrip::theater_chase_update() {
    for(unsigned int i=0; i< led_count; i++) {
        if ((i + index) % 3 == 0) {
            strip->setPixelColor(i, color1);
        } else {
            strip->setPixelColor(i, color2);
        }
    }
}

/**
    Fade color1 into color2 progressively using linear interpolation of both
    colors.
*/
inline void LEDStrip::fade(uint32_t color1, uint32_t color2, uint16_t steps,
        uint16_t interval) {
    pattern = FADE;
    index = 0;
    total_steps = steps;
    this->interval = interval;
    this->color1 = color1;
    this->color3 = color1;
    this->color2 = color2;
    this->direction = FORWARD;
}

/**
    Logic to update the fade pattern.
*/
void LEDStrip::fade_update() {
    // Calculate linear interpolation between color1 and color2
    // Optimize order of operations to minimize truncation error
    uint8_t red = ((Red(color1) * (total_steps - index))
        + (Red(color2) * index)) / total_steps;
    uint8_t green = ((Green(color1) * (total_steps - index))
        + (Green(color2) * index)) / total_steps;
    uint8_t blue = ((Blue(color1) * (total_steps - index))
        + (Blue(color2) * index)) / total_steps;

    color1 = strip->Color(red, green, blue);

    for (unsigned  int i = 0; i < led_count; i++) {
        strip->setPixelColor(i, color1);
    }
}
