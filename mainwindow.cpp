#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "photo_frame.h"

using namespace std;
using namespace cv;

Mat image[100];
int currentstep=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Photo_frame.setEnabled(false);
    ui->setupUi(this);
    this->setWindowTitle(tr("Tool Box"));
    image[0]=imread("D://Photos/BB8/BB8.jpg");
//image[0]=imread("D://Photos/BB8/15609246_1219648224796806_584233906_o.jpg");
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
void MainWindow::on_blur_btn_clicked()
{

    GaussianBlur(image[currentstep],image[currentstep+1],Size(9,9),0,0);
    photo_window_update();
    currentstep++;
    ui->label->setText(QString::number(currentstep));


}



void MainWindow::on_undo_btn_clicked()
{
    //image[0]=imread("D://Photos/BB8/15609246_1219648224796806_584233906_o.jpg");
    if(currentstep>0)
        ui->undo_btn->setEnabled(true);
    else
        ui->undo_btn->setEnabled(false);

    if(image[currentstep+1].size!=0)
        ui->redo_btn->setEnabled(true);
    else
        ui->redo_btn->setEnabled(false);
}

void MainWindow::on_redo_btn_clicked()
{
    //image[0]=imread("D://Photos/BB8/BB8.jpg");
    if(currentstep>0)
        ui->undo_btn->setEnabled(true);
    else
        ui->undo_btn->setEnabled(false);

    if(image[currentstep+1].size!=0)
        ui->redo_btn->setEnabled(true);
    else
        ui->redo_btn->setEnabled(false);
}
