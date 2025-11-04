#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSelect_image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::homePath(),
                                                    tr("Image Files (*.bmp)"));
    if (!fileName.isEmpty()) {
        Mat image = imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);
    }
}

