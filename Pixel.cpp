#include "Pixel.h"

Pixel::Pixel() {
    this->value = 0;
    this->x = 0;
    this->y = 0;
}

Pixel::Pixel(uint8_t value, int x, int y){
    this->value = value;
    this->x = x;
    this->y = y;
}

Pixel* Pixel::copy(){
    return new Pixel(this->value, this->x, this->y);
}

Pixel::~Pixel(){ }
