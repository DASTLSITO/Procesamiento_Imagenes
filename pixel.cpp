#include "pixel.h"

pixel::pixel() {
    this->value = 0;
    this->x = 0;
    this->y = 0;
}

pixel::pixel(uint8_t value, int x, int y){
    this->value = value;
    this->x = x;
    this->y = y;
}

pixel* pixel::copy(){
    return new pixel(this->value, this->x, this->y);
}

pixel::~pixel(){ }
