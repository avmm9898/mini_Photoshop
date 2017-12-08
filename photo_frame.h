#ifndef PHOTO_FRAME_H
#define PHOTO_FRAME_H


#include <QDialog>
#include <opencv2/opencv.hpp>  //all in one
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <Qvector>
#include <QRgb>
#include "QPushButton"
#include "QVBoxLayout"
#include "QLabel"

using namespace cv;
extern Mat image[];
extern int currentstep;

namespace Ui {
class photo_frame;
}

class photo_frame : public QDialog
{
    Q_OBJECT

public:
    explicit photo_frame(QWidget *parent = 0);
    ~photo_frame();

    void photo_frame::frame_in();

public slots:
    QImage photo_frame::Mat2QImage(Mat src);

private:
    Ui::photo_frame *ui;

    QPixmap Pixmap;
    //QLabel *Photo_label= new QLabel("");

};

#endif // PHOTO_FRAME_H
