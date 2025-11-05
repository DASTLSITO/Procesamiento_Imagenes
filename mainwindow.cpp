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

QImage* MatToQImage(Mat& mat) {
    if (mat.type() == CV_8UC3) { // RGB image
        QImage* qImage = new QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
        qImage->rgbSwap();
        return qImage;
    } else if (mat.type() == CV_8UC1) { // Grayscale image
        return new QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
    }
    // Handle other formats if needed, or return a null QImage
    return new QImage();
}

void MainWindow::on_actionSelect_image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::homePath(),
                                                    tr("Image Files (*.bmp)"));
    if (fileName.isEmpty()) {
        return;
    }

    imageMat = imread(fileName.toStdString(), IMREAD_GRAYSCALE);
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
    image = Image(columns, rows, pixels);
    QImage* qImage = MatToQImage(imageMat);
    Dialog* imageWindow = new Dialog(this, qImage);
    imageWindow->show();

}


