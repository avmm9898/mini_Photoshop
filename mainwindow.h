#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QBitmap>
#include <QPicture>
#include <QPixmap>

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
    QImage * MainWindow::greyScale(QImage * origin);
    QImage * MainWindow::brightnessScale(bool set,int value,QImage * origin);
    QImage * MainWindow::warm(bool set, int value, QImage * origin);
    QImage * MainWindow::saturation(bool set, int value, QImage *origin);
    QImage * MainWindow::blur(QImage * origin);
    QImage * MainWindow::sharpen(QImage * origin);
    void undo_redo_enable();

private slots:

    void on_BrightnessSlider_valueChanged(int value);
    void on_warmSlider_valueChanged(int value);
    void on_greybtn_clicked();

    void on_actionOpen_File_triggered();

    void on_actionSave_File_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_brightnessset_btn_clicked();

    void on_warmset_btn_clicked();

    void on_saturation_btn_clicked();

    void on_blur_clicked();

    void on_Sharpen_clicked();

    void on_saturation_slider_valueChanged(int value);



private:
    Ui::MainWindow *ui;
    QPixmap pixmap;
    //QVector<QImage> *Image;   //可記錄100個步驟
    QImage *Image[100];
    int currentstep=0;
    int brightnessdelta=0;
    int color_temperaturedelta=0;
    int saturationdelta=0;
};

#endif // MAINWINDOW_H
