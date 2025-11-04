#ifndef IMAGE_H
#define IMAGE_H
#include "pixel.h"

class image
{
public:
    // Constructors
    image();
    image(int, int);
    image(int, int, pixel**);

    // Destructors
    ~image();

    // Attributes
    int columns;
    int rows;
    pixel** pixels;

    // Methods
    image* copy();

};

#endif // IMAGE_H
