//
// Created by Kodiko Dytis on 09/05/16.
//

#include "LEDStrip.h"

LEDStrip::LEDStrip(uint32_t data_pin_left,uint32_t data_pin_right, uint32_t led_count) {
    //   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
    //   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

    this->led_count = led_count;

    strips[LEFT]  = new Adafruit_NeoPixel(this->led_count, data_pin_left, NEO_GRB + NEO_KHZ800);
    strips[RIGHT] = new Adafruit_NeoPixel(this->led_count, data_pin_right, NEO_GRB + NEO_KHZ800);

    strips[LEFT]->begin();
    strips[RIGHT]->begin();
    strips[LEFT]->show();  // Initialize all pixels to 'off
    strips[RIGHT]->show(); // Initialize all pixels to 'off
}


void LEDStrip::theater_chase(uint32_t color, uint8_t wait) {
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < led_count; i=i+3) {
                strips[LEFT]->setPixelColor(i+q, color);    //turn every third pixel on
                strips[RIGHT]->setPixelColor(i+q, color);   //turn every third pixel on
            }
            strips[LEFT]->show();
            strips[RIGHT]->show();

            delay(wait);

            for (uint16_t i=0; i < led_count; i=i+3) {
                strips[LEFT]->setPixelColor(i+q, 0);        //turn every third pixel off
                strips[RIGHT]->setPixelColor(i+q, 0);       //turn every third pixel off
            }
        }
    }
}

void LEDStrip::goal_effect(byte team) {
    theater_chase(RED, 10);
}