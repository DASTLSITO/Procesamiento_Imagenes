#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image* img = new image(3, 4);
    image* imgCopy = img->copy();
    std::cout<<imgCopy->columns<<std::endl;
    std::cout<<imgCopy->rows<<std::endl;
    for(int i = 0; i < imgCopy->columns; i++){
        for(int j = 0; j < imgCopy->columns; j++)
        {
            std::cout<<imgCopy->pixels[i][j].x<<std::endl;
            std::cout<<imgCopy->pixels[i][j].y<<std::endl;
            std::cout<<static_cast<int>(imgCopy->pixels[i][j].value)<<std::endl;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
