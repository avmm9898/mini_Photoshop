#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "QVBoxLayout"
#include "QLabel"


using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    ui->setupUi(this);
    this->setWindowTitle(tr("Tool Box"));



    //QString filename=QFileDialog::getOpenFileName(this,tr("Select an Image"),"/home","Images(*.png *.bmp *.jpg)");
    //Mat image=imread(filename.toStdString());
    *image=imread("D://Photos/BB8/BB8.jpg");  //use / instead \

    //cvtColor(image,image,CV_RGB2BGR);
    //imshow("new",image);
    //QImage img=Mat2QImage(image);
    //QImage img= QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888);
    // img = img.scaled(ui->QImgShow->size());
    // 根據Label設置圖片大小,並顯示
    //ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size()));
    QVBoxLayout *lay= new QVBoxLayout(this);
    QLabel *Photo_frame= new QLabel("HELLLLLLLLLLLLLLLLLLLLLLLLo");
    lay->addWidget(Photo_frame);


    QPixmap Pixmap=QPixmap::fromImage(Mat2QImage(*image));
    int fix_image_height=800;
    Pixmap=Pixmap.scaledToHeight(fix_image_height);
    int image_width=Pixmap.width();             //which is the width after scaled
    Photo_frame->setGeometry(0,0,image_width,fix_image_height);
    Photo_frame->setPixmap(Pixmap);
    ui->scrollAreaWidgetContents->setLayout(lay);

    //this->setGeometry(50,50,image_width+50,fix_image_height+50);
    this->setFixedSize(image_width+50,fix_image_height+50);
    /*QVBoxLayout *lay= new QVBoxLayout(this);
    for(int i=0;i<=15;i++){

        QLabel *Bootto= new QLabel("HELLLLLLLLLLLLLLLLLLLLLLLLo");
        lay->addWidget(Bootto);

    }
    ui->scrollAreaWidgetContents->setLayout(lay);*/
    //ui->scrollArea->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
    //ui->scrollArea->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOn);



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
