#include "dialog.h"
#include "ui_dialog.h"

#include <QLabel>
Dialog::Dialog(QWidget *parent, const Mat& mat, const QString& title)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , mat(mat.clone())
{
    this->setObjectName(title);
    this->qImage = new QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
    this->setFixedSize(qImage->width() + 10, qImage->height() + 10);
    ui->setupUi(this);
    setWindowTitle(title);
    ui->label->setPixmap(QPixmap::fromImage(*qImage));
    ui->label->setGeometry(5, 5, qImage->width(), qImage->height());
}

void Dialog::MatToQImage(Mat& mat) {
    this->qImage = new QImage(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
    this->setFixedSize(qImage->width() + 10, qImage->height() + 10);
    ui->label->setPixmap(QPixmap::fromImage(*qImage));
    ui->label->setGeometry(5, 5, qImage->width(), qImage->height());
}

Dialog::~Dialog()
{
    delete ui;
}
