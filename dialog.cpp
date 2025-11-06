#include "dialog.h"
#include "ui_dialog.h"

#include <QLabel>
Dialog::Dialog(QWidget *parent, const Mat& mat, const QString& title)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{

    QImage* qImage = MatToQImage(mat);
    this->setFixedSize(qImage->width() + 10, qImage->height() + 10);
    ui->setupUi(this);
    setWindowTitle(title);
    ui->label->setPixmap(QPixmap::fromImage(*qImage));
    ui->label->setGeometry(5, 5, qImage->width(), qImage->height());
}

QImage* Dialog::MatToQImage(const Mat& mat) {
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

Dialog::~Dialog()
{
    delete ui;
}
