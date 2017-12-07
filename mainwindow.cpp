#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "photo_frame.h"

using namespace std;
using namespace cv;

Mat image;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Photo_frame.setEnabled(false);
    ui->setupUi(this);
    this->setWindowTitle(tr("Tool Box"));


    //QString filename=QFileDialog::getOpenFileName(this,tr("Select an Image"),"/home","Images(*.png *.bmp *.jpg)");
    //Mat image=imread(filename.toStdString());

    //cvtColor(image,image,CV_RGB2BGR);
    //imshow("new",image);




}
QImage MainWindow::Mat2QImage(const Mat src){

    if(src.type()==CV_8UC1){
        QVector<QRgb> colorTable;
        for(int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        const uchar *qImageBuffer=(const uchar*)src.data;
        QImage img(qImageBuffer,src.cols,src.rows,src.step,QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    if(src.type()==CV_8UC3){
        const uchar *qImageBuffer=(const uchar*)src.data;
        QImage img(qImageBuffer,src.cols,src.rows,src.step,QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else{
        cout<<"Error!";
        return QImage();
    }

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::photo_window_update(){
    static photo_frame P_frame;
    P_frame.frame_in();
    P_frame.show();
}
void MainWindow::on_pushButton_clicked()
{


    image=imread("D://Photos/BB8/BB8.jpg");


}

void MainWindow::on_pushButton_2_clicked()
{
    image=imread("D://Photos/BB8/P1060866.JPG");

}

void MainWindow::on_pushButton_3_clicked()
{
    photo_window_update();
}
