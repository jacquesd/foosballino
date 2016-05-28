//
// Created by Kodiko Dytis on 09/05/16.
//

#include "LEDStrip.h"

// Returns the Red component of a 32-bit color
uint8_t Red(uint32_t color) {
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color) {
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color) {
    return color & 0xFF;
}


LEDStrip::LEDStrip(uint32_t led_count, uint32_t data_pin) {
    //   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
    //   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

    this->led_count = led_count;

    strip = new Adafruit_NeoPixel(this->led_count, data_pin, NEO_GRB + NEO_KHZ800);

    strip->begin();
    strip->show();  // Initialize all pixels to 'off

    last_update = millis();
    set_default();
}

void LEDStrip::update() {
    if (millis() - last_update < interval) {
        return;
    }

    last_update = millis();
    switch(pattern) {
        case THEATER_CHASE:
            theater_chase_update();
            break;
        case SCANNER:
            scanner_update();
            break;
        case FADE:
            fade_update();
            break;
        default:
            break;
    }
}

void LEDStrip::increment() {
    if (direction == FORWARD) {
        index++;
        if (index >= total_steps) {
            index = 0;
            if (pattern == SCANNER) {
                this->set_default();
            }
        }
    } else {// direction == REVERSE
        index--;
        if (index <= 0) {
            index = total_steps - 1;
            if (pattern == SCANNER) {
                this->set_default();
            }
        }
    }
}

void LEDStrip::set_default() {
    pattern = NONE;
    for (uint32_t i=0; i < led_count - 1; i=i+2) {
        strip->setPixelColor(i, 160, 160, 160);
        strip->setPixelColor(i + 1, 0, 0, 0);
    }
    strip->show();

}

void LEDStrip::theater_chase(uint32_t color1, uint32_t color2, uint8_t interval, Direction direction = FORWARD) {
    pattern = THEATER_CHASE;
    index = 0;
    total_steps = led_count;
    this->color1 = color1;
    this->color2 = color2;
    this->interval = interval;
    this->direction = direction;
}

void LEDStrip::theater_chase_update() {
    for(unsigned int i=0; i< led_count; i++) {
        if ((i + index) % 3 == 0) {
            strip->setPixelColor(i, color1);
        } else {
            strip->setPixelColor(i, color2);
        }
    }
    strip->show();
    increment();
}

void LEDStrip::scanner(uint32_t color, uint8_t interval, Direction direction) {
    pattern = SCANNER;
    index = 0;
    total_steps = (led_count - 1) * 2;
    this->interval = interval;
    this->color1 = color;
}

void LEDStrip::scanner_update() {
    for (int i = 0; i < led_count; i++) {
        if (i == index) { // Scan Pixel to the right
            strip->setPixelColor(i, color1);
        } else if (i == total_steps - index) { // Scan Pixel to the left
            strip->setPixelColor(i, color1);
        } else { // Fading tail
            strip->setPixelColor(i, dim_color(strip->getPixelColor(i)));
        }
    }
    strip->show();
    increment();
}

void LEDStrip::fade(uint32_t color1, uint32_t color2, uint16_t steps, uint8_t interval) {
    pattern = FADE;
    index = 0;
    total_steps = steps;
    this->interval = interval;
    this->color1 = color1;
    this->color2 = color2;
}

void LEDStrip::fade_update() {
    // Calculate linear interpolation between color1 and color2
    // Optimise order of operations to minimize truncation error
    uint8_t red = ((Red(color1) * (total_steps - index)) + (Red(color2) * index)) / total_steps;
    uint8_t green = ((Green(color1) * (total_steps - index)) + (Green(color2) * index)) / total_steps;
    uint8_t blue = ((Blue(color1) * (total_steps - index)) + (Blue(color2) * index)) / total_steps;
    color1 = strip->Color(red, green, blue);

    for (unsigned  int i = 0; i < led_count; i++) {
        strip->setPixelColor(i, color1);
    }
    strip->show();
    increment();
}

uint32_t LEDStrip::dim_color(uint32_t color) {
    // Shift R, G and B components one bit to the right
    uint32_t dimmed_color = strip->Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
    return dimmed_color;
}