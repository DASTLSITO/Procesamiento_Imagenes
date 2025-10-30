#ifndef PIXEL_H
#define PIXEL_H

#include "cstdint"

class pixel
{
public:
    // Constructors
    pixel();
    pixel(uint8_t, int, int);

    // Destructors
    ~pixel();

    // Attributes
    uint8_t value;
    int x;
    int y;

    // Methods
    pixel* copy();



};

#endif // PIXEL_H
