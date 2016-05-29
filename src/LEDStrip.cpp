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


LEDStrip::LEDStrip(uint32_t LedCount, uint32_t DataPin) {
    //   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
    //   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

    this->LedCount = LedCount;
    // pinMode(DataPin, INPUT_PULLUP);

    strip = new Adafruit_NeoPixel(this->LedCount, DataPin, NEO_GRB + NEO_KHZ800);

    strip->begin();
    strip->show();  // Initialize all pixels to 'off

    LastUpdate = millis();
    flood_light();
}

void LEDStrip::update() {
    if (millis() - LastUpdate < Interval) {
        return;
    }

    LastUpdate = millis();
    switch(Pattern) {
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
    if (Direction == FORWARD) {
        Index++;
        if (Index >= TotalSteps) {
            Index = 0;
            switch (Pattern) {
                case SCANNER:
                    this->flood_light();
                    break;
                case FADE:
                    fade(Color2, Color3, 200, 40);

                    break;
            }
        }
    } else {// Direction == REVERSE
        Index--;
        if (Index <= 0) {
            Index = TotalSteps - 1;
            switch (Pattern) {
                case SCANNER:
                    this->flood_light();
                    break;
                case FADE:
                    fade(Color2, Color3, 200, 40);

                    break;
            }
        }
    }
}

void LEDStrip::flood_light() {
    Pattern = NONE;
    Interval = 50;
    for (uint32_t i=0; i < LedCount - 1; i=i+2) {
        strip->setPixelColor(i, 160, 160, 160);
        strip->setPixelColor(i + 1, 0, 0, 0);
    }
    strip->show();

}

void LEDStrip::theater_chase(uint32_t Color1, uint32_t Color2, uint8_t Interval, direction Direction = FORWARD) {
    Pattern = THEATER_CHASE;
    Index = 0;
    TotalSteps = LedCount;
    this->Color1 = Color1;
    this->Color2 = Color2;
    this->Interval = Interval;
    this->Direction = Direction;
}

void LEDStrip::theater_chase_update() {
    for(unsigned int i=0; i< LedCount; i++) {
        if ((i + Index) % 3 == 0) {
            strip->setPixelColor(i, Color1);
        } else {
            strip->setPixelColor(i, Color2);
        }
    }
    strip->show();
    increment();
}

void LEDStrip::scanner(uint32_t color, uint8_t Interval, direction Direction) {
    this->Interval = Interval;
    this->Color1 = color;
    this->Direction = Direction;
    Pattern = SCANNER;
    TotalSteps = (LedCount - 1) * 2;
    Index = Direction == FORWARD ? 0 : TotalSteps;

}

void LEDStrip::scanner_update() {
    unsigned int pos = 0;
    for (unsigned int i = 0; i < LedCount; i++) {
        pos = Direction == FORWARD ? i : (LedCount - 1 - i);
        if (i == Index) { // Scan Pixel to the right
                strip->setPixelColor(pos, Color1);
        } else if (((signed) i) == TotalSteps - Index) { // Scan Pixel to the left
                strip->setPixelColor(pos, Color1);
        } else { // Fading tail
                strip->setPixelColor(pos, dim_color(strip->getPixelColor(pos)));
        }
    }
    strip->show();
    increment();
}

void LEDStrip::fade(uint32_t Color1, uint32_t Color2, uint16_t steps, uint8_t Interval) {
    Pattern = FADE;
    Index = 0;
    TotalSteps = steps;
    this->Interval = Interval;
    this->Color1 = Color1;
    this->Color3 = Color1;
    this->Color2 = Color2;
    this->Direction = FORWARD;
}

void LEDStrip::fade_update() {
    // Calculate linear interpolation between Color1 and Color2
    // Optimise order of operations to minimize truncation error
    uint8_t red = ((Red(Color1) * (TotalSteps - Index)) + (Red(Color2) * Index)) / TotalSteps;
    uint8_t green = ((Green(Color1) * (TotalSteps - Index)) + (Green(Color2) * Index)) / TotalSteps;
    uint8_t blue = ((Blue(Color1) * (TotalSteps - Index)) + (Blue(Color2) * Index)) / TotalSteps;
    Color1 = strip->Color(red, green, blue);

    for (unsigned  int i = 0; i < LedCount; i++) {
        strip->setPixelColor(i, Color1);
    }
    strip->show();
    increment();
}

uint32_t LEDStrip::dim_color(uint32_t color) {
    // Shift R, G and B components one bit to the right
    uint32_t dimmed_color = strip->Color(Red(color) >> 1, Green(color) >> 1, Blue(color) >> 1);
    return dimmed_color;
}
