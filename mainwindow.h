#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "photo_frame.h"
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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //photo_frame P_frame;
public slots:
    QImage MainWindow::Mat2QImage(Mat src);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

private slots:
    void MainWindow::photo_window_update();

    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
