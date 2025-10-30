#include "image.h"

image::image() {
    this->columns = 0;
    this->rows = 0;
    this->pixels = nullptr;
}

image::image(int columns, int rows, pixel** pixels){
    this->columns = columns;
    this->rows = rows;
    this->pixels = pixels;
}

image::image(int columns, int rows){
    this->columns = columns;
    this->rows = rows;
    pixels = new pixel*[columns];
    for(int i = 0; i < columns; i++){
        pixels[i] = new pixel[rows];
        for(int j = 0; j < rows; j++)
        {
            pixels[i][j] = pixel(0, i, j);
        }
    }
}

image* image::copy(){
    image* imageCopy;
    if(this->pixels != nullptr){
        imageCopy = new image(columns, rows);
        for(int i = 0; i < imageCopy->columns; i++){
            for(int j = 0; j < imageCopy->rows; j++)
            {
                imageCopy->pixels[i][j] = *this->pixels[i][j].copy();
            }
        }
    }
    else{
        imageCopy = new image();
    }
    return imageCopy;
}

image::~image(){
    delete pixels;
}
