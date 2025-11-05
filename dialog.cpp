#include "dialog.h"
#include "ui_dialog.h"

#include <QLabel>
Dialog::Dialog(QWidget *parent, QImage *qImage)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setFixedSize(qImage->width(), qImage->height());
    ui->label->setPixmap(QPixmap::fromImage(*qImage));
    ui->label->setWindowTitle("OpenCV Image");
    ui->label->show();
}

Dialog::~Dialog()
{
    delete ui;
}
