#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;
using namespace cv;

Mat imageMat;
Image image;

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


Image* MatToImage(Mat& imageMat){
    int columns = imageMat.cols;
    int rows = imageMat.rows;
    Pixel** pixels = new Pixel*[columns];
    for(int i = 0; i < columns; i++){
        pixels[i] = new Pixel[rows];
        for(int j = 0; j < rows; j++){
            pixels[i][j] = Pixel(imageMat.at<uint8_t>(j, i), i, j);
            //cout<<pixels[i][j].x<<"\t"<<pixels[i][j].y<<"\t"<<static_cast<int>(pixels[i][j].value)<<endl;
        }
    }
    return new Image(columns, rows, pixels);
}

Mat GetInverseImage(Mat& originalImage){
    Mat imageCopy = originalImage.clone();
    for(int i = 0; i < imageCopy.rows; i++){
        for(int j = 0; j < imageCopy.cols; j++){
            imageCopy.at<uint8_t>(i, j) = 255 - imageCopy.at<uint8_t>(i, j);
        }
    }
    return imageCopy;
}

void MainWindow::on_actionSelect_image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::currentPath().replace("build/Desktop-Debug/bin", ""),
                                                    tr("Image Files (*.bmp)"));
    if (fileName.isEmpty()) {
        return;
    }

    imageMat = imread(fileName.toStdString(), IMREAD_GRAYSCALE);
    //Image* image = MatToImage(imageMat);

    Mat imageInverse = GetInverseImage(imageMat);
    Dialog* imageWindow = new Dialog(this, imageMat, "Imagen Original");
    imageWindow->show();
    Dialog* imageWindowInverse = new Dialog(this, imageInverse, "Imagen Inversa");
    imageWindowInverse->show();


}


