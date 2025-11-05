#ifndef PIXEL_H
#define PIXEL_H

#include "cstdint"

class Pixel
{
public:
    // Constructors
    Pixel();
    Pixel(uint8_t, int, int);

    // Destructors
    ~Pixel();

    // Attributes
    uint8_t value;
    int x;
    int y;

    // Methods
    Pixel* copy();



};

#endif // PIXEL_H
