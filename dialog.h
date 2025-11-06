#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <opencv2/core.hpp>

using namespace cv;
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr, const Mat& = Mat(), const QString& = "Dialog");
    ~Dialog();

    QImage* MatToQImage(const Mat&);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
