#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>  //all in one
#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <Qvector>
#include <QRgb>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    QImage MainWindow::Mat2QImage(const cv::Mat src);

private:
    Ui::MainWindow *ui;
    Mat *image;
private slots:


};

#endif // MAINWINDOW_H
