#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;
using namespace cv;

Mat matOriginal;
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

Mat GetInverseImage(Mat& originalMat){
    Mat matCopy = originalMat.clone();
    for(int i = 0; i < matCopy.rows; i++){
        for(int j = 0; j < matCopy.cols; j++){
            matCopy.at<uint8_t>(i, j) = 255 - matCopy.at<uint8_t>(i, j);
        }
    }
    return matCopy;
}

Mat GetBinaryImage(Mat& originalMat, uint8_t threshold = 125){
    Mat matCopy = originalMat.clone();
    for(int i = 0; i < matCopy.rows; i++){
        for(int j = 0; j < matCopy.cols; j++){
            matCopy.at<uint8_t>(i, j) = originalMat.at<uint8_t>(i, j) < threshold ? 0 : 255;
        }
    }
    return matCopy;
}

Mat GetMinimumValueImage(Mat& originalMat, Mat& thresholdMat){
    Mat matCopy = originalMat.clone();
    for(int i = 0; i < matCopy.rows; i++){
        for(int j = 0; j < matCopy.cols; j++){
            matCopy.at<uint8_t>(i, j) = originalMat.at<uint8_t>(i, j) < thresholdMat.at<uint8_t>(i, j)
                                            ? originalMat.at<uint8_t>(i, j)
                                            : thresholdMat.at<uint8_t>(i, j);
        }
    }
    return matCopy;
}

Mat GetMirrorImage(Mat& originalMat){
    Mat matCopy = Mat(originalMat.cols, originalMat.rows, originalMat.type());
    for(int i = 0; i < matCopy.rows; i++){
        for(int j = 0; j < matCopy.cols; j++){
            matCopy.at<uint8_t>(i, j) = originalMat.at<uint8_t>(j, i);
        }
    }
    return matCopy;
}



Mat GetMirror90DImage(Mat& originalMat){
    Mat matCopy = Mat(originalMat.cols, originalMat.rows, originalMat.type());
    for(int i = 0; i < matCopy.rows; i++){
        for(int j = 0; j < matCopy.cols; j++){
            matCopy.at<uint8_t>(i, j) = originalMat.at<uint8_t>(j, i);
        }
    }
    return matCopy;
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

    matOriginal = imread(fileName.toStdString(), IMREAD_GRAYSCALE);
    //Image* image = MatToImage(matOriginal);

    Mat matInverse = GetInverseImage(matOriginal);
    Mat matMirror = GetMirrorImage(matOriginal);
    Mat mat90DImage = GetMirror90DImage(matOriginal);
    Mat matBinary = GetBinaryImage(matOriginal, 80);
    Mat matMinValue = GetMinimumValueImage(matOriginal, matBinary);
    Dialog* imageWindow = new Dialog(this, matOriginal, "Imagen Original");
    imageWindow->show();
    Dialog* imageWindowInverse = new Dialog(this, matInverse, "Imagen Inversa");
    imageWindowInverse->show();
    Dialog* imageWindowMirror = new Dialog(this, matMirror, "Imagen Espejo");
    imageWindowMirror->show();
    //Dialog* imageWindowMirror90D = new Dialog(this, mat90DImage, "Imagen Espejo 90 Grados");
    //imageWindowMirror90D->show();
    Dialog* imageWindowBinary = new Dialog(this, matBinary, "Imagen Binaria");
    imageWindowBinary->show();
    Dialog* imageWindowMinValue = new Dialog(this, matMinValue, "Imagen minimo valor");
    imageWindowMinValue->show();
}


