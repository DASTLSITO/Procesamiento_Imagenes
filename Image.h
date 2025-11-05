#ifndef IMAGE_H
#define IMAGE_H
#include "Pixel.h"

class Image
{
public:
    // Constructors
    Image();
    Image(int, int);
    Image(int, int, Pixel**);

    // Destructors
    ~Image();

    // Attributes
    int columns;
    int rows;
    Pixel** pixels;

    // Methods
    Image* copy();

};

#endif // Image_H
