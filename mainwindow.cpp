#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    ui->setupUi(this);
    this->setWindowTitle(tr("GrayScale"));
    this->setFixedSize(1000,600);


    QString filename=QFileDialog::getOpenFileName(this,tr("Select an Image"),"/home","Images(*.png *.bmp *.jpg)");
    Mat image=imread(filename.toStdString());
    //cvtColor(image,image,CV_RGB2BGR);
    imshow("new",image);
    //QImage img=Mat2QImage(image);
    //QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
    // img = img.scaled(ui->QImgShow->size());
    // 根據Label設置圖片大小,並顯示
    //ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size()));
    QPixmap Pixmap=QPixmap::fromImage(Mat2QImage(image));



    //ui->photo_frame->setFixedSize(800,800);
    ui->photo_frame->setGeometry(0,0,800,800);
    Pixmap=Pixmap.scaledToHeight(ui->photo_frame->height());
    ui->photo_frame->setPixmap(Pixmap);
    int x=Pixmap.width();
    ui->label_2->setText(QString::number(x));

    this->setFixedSize(x+300,900);


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
