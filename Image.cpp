#include "Image.h"

Image::Image() {
    this->columns = 0;
    this->rows = 0;
    this->pixels = nullptr;
}

Image::Image(int columns, int rows, Pixel** pixels){
    this->columns = columns;
    this->rows = rows;
    this->pixels = pixels;
}

Image::Image(int columns, int rows){
    this->columns = columns;
    this->rows = rows;
    pixels = new Pixel*[columns];
    for(int i = 0; i < columns; i++){
        pixels[i] = new Pixel[rows];
        for(int j = 0; j < rows; j++)
        {
            pixels[i][j] = Pixel(0, i, j);
        }
    }
}

Image* Image::copy(){
    Image* ImageCopy;
    if(this->pixels != nullptr){
        ImageCopy = new Image(columns, rows);
        for(int i = 0; i < ImageCopy->columns; i++){
            for(int j = 0; j < ImageCopy->rows; j++)
            {
                ImageCopy->pixels[i][j] = *this->pixels[i][j].copy();
            }
        }
    }
    else{
        ImageCopy = new Image();
    }
    return ImageCopy;
}

Image::~Image(){
    delete pixels;
}
