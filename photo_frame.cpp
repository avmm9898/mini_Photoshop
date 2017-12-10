#include "photo_frame.h"
#include "ui_photo_frame.h"
using namespace cv;
using namespace std;

float zoom_times=1;
float zoom_scale=0;
int pixmap_width=0;
int pixmap_height=0;

int begin_pointX;
int begin_pointY;

photo_frame::photo_frame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::photo_frame)
{    
    ui->setupUi(this);

    ui->label->setMouseTracking(true);

    //QVBoxLayout *lay = new QVBoxLayout(this);
    this->setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    //lay->addWidget(ui->label);
    //lay->alignment()
    //ui->scrollAreaWidgetContents->setLayout(lay);

    /* static QString size;


    Pixmap=QPixmap::fromImage(Mat2QImage(image[currentstep]));
    size=QString::number(Pixmap.width())+"x"+QString::number(Pixmap.height());

int window_height=900;
    int window_width=Pixmap.width()*800/Pixmap.height();             //which is the width after scaled
    ui->label->setPixmap(Pixmap);
    this->resize(window_width+50,window_height+50);*/

}
void photo_frame::frame_load(Mat frame){
    if(!frame.empty()){
        QString size;

        Pixmap=QPixmap::fromImage(Mat2QImage(frame));
        pixmap_width=Pixmap.width();
        pixmap_height=Pixmap.height();
        size=QString::number(pixmap_width)+"x"+QString::number(pixmap_height);
        this->setWindowTitle(size);
        int window_height=900;
        int window_width=pixmap_width*window_height/pixmap_height;             //which is the width after scaled
        this->setGeometry(100,100,window_width,window_height);

        //this->resize(window_width+50,window_height+100);
        on_fit_btn_clicked();

        //imshow("new",image[currentstep]);
    }
}
void photo_frame::frame_update(Mat frame){
    if(!frame.empty()){

        Pixmap=QPixmap::fromImage(Mat2QImage(frame));
        QString size;
        pixmap_width=Pixmap.width();
        pixmap_height=Pixmap.height();
        size=QString::number(pixmap_width)+"x"+QString::number(pixmap_height);
        this->setWindowTitle(size);

        int pixmap_height_t=float(pixmap_height)*zoom_times;
        QPixmap ZPixmap=Pixmap.scaledToHeight(pixmap_height_t);

        ui->label->setPixmap(ZPixmap);
    }
}

QImage photo_frame::Mat2QImage(const Mat src){
    //return QImage((unsigned char*) src.data, src.cols, src.rows, QImage::Format_RGB888).rgbSwapped();
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

photo_frame::~photo_frame()
{
    delete ui;
}



void photo_frame::on_zoomin_btn_clicked()
{
    if(zoom_times<2){
        zoom_times= zoom_times+0.05;}
    int pixmap_height_t=int(pixmap_height*zoom_times);
    //ui->fit_btn->setText(QString::number(pixmap_height_t));
    QPixmap ZPixmap=Pixmap.scaledToHeight(pixmap_height_t);
    ui->label->setPixmap(ZPixmap);
}

void photo_frame::on_zoomout_btn_clicked()
{
    if(zoom_times>0.1){
        zoom_times=zoom_times-0.05;}

    int pixmap_height_t=int(pixmap_height*zoom_times);

    QPixmap ZPixmap=Pixmap.scaledToHeight(pixmap_height_t);
    ui->label->setPixmap(ZPixmap);


}

void photo_frame::on_fit_btn_clicked()
{
    float pixmap_height_f=float(ui->scrollArea->height())-40;
    zoom_times=pixmap_height_f/float(pixmap_height);
    int pixmap_height_t=pixmap_height*zoom_times;
    QPixmap ZPixmap=Pixmap.scaledToHeight(pixmap_height_t);
    if(ui->scrollArea->width()<ZPixmap.width()){
        if(!this->isMaximized()){
       this->resize(ZPixmap.width()+20,this->height());}
    }
    ui->label->setPixmap(ZPixmap);
}

void photo_frame::on_ori_btn_clicked()
{
    zoom_times=1;
    int pixmap_height_t=int(pixmap_height*zoom_times);

    QPixmap ZPixmap=Pixmap.scaledToHeight(pixmap_height_t);
    ui->label->setPixmap(ZPixmap);
}


void photo_frame::mouseMoveEvent(QMouseEvent *event){

    //static int oldx=0,oldy=0;
    int x=event->x();
    int y=event->y();


    int P_x=(ui->scrollArea->width()-pixmap_width*zoom_times)/2+1;
    int P_y=(ui->scrollArea->height()-pixmap_height*zoom_times)/2+1;

    int realx=(x-P_x)/zoom_times;
    int realy=(y-P_y-ui->scrollArea->y())/zoom_times;
    if(realx>Pixmap.width())
        realx=Pixmap.width();
    else if(realx<0)
        realx=0;
    if(realy>Pixmap.height())
        realy=Pixmap.height();
    else if(realx<0)
        realy=0;

    Mat drawrec;
    drawrec=image[currentstep].clone();   //  if we use "=", the right Mat will change whith the left Mat
    rectangle(drawrec, Point(begin_pointX,begin_pointY), Point(realx,realy), Scalar(0,0,255), 5);
    frame_update(drawrec);
    //ui->test->setText(QString(tr("(%1, %2)")).arg(QString::number(P_x), QString::number(P_y)));//arg()函數可以替換掉QString中出現的佔位符。佔位符為%加位置，如%1、%2。



}

void photo_frame::mousePressEvent(QMouseEvent *event){
    on_fit_btn_clicked();
    int x=event->x();
    int y=event->y();
    int P_x=(ui->scrollArea->width()-pixmap_width*zoom_times)/2+1;
    int P_y=(ui->scrollArea->height()-pixmap_height*zoom_times)/2+1;

    begin_pointX=(x-P_x)/zoom_times;
    begin_pointY=(y-P_y-ui->scrollArea->y())/zoom_times;
    if(begin_pointX>Pixmap.width())
        begin_pointX=Pixmap.width();
    else if(begin_pointX<0)
        begin_pointX=0;
    if(begin_pointY>Pixmap.height())
        begin_pointY=Pixmap.height();
    else if(begin_pointY<0)
        begin_pointY=0;



}

void photo_frame::mouseReleaseEvent(QMouseEvent *event){

    int x=event->x();
    int y=event->y();
    int P_x=(ui->scrollArea->width()-pixmap_width*zoom_times)/2+1;
    int P_y=(ui->scrollArea->height()-pixmap_height*zoom_times)/2+1;

    int end_pointX=(x-P_x)/zoom_times;
    int end_pointY=(y-P_y-ui->scrollArea->y())/zoom_times;
    if(end_pointX>Pixmap.width())
        end_pointX=Pixmap.width();
    else if(end_pointX<0)
        end_pointX=0;
    if(end_pointY>Pixmap.height())
        end_pointY=Pixmap.height();
    else if(end_pointY<0)
        end_pointY=0;

    QMessageBox message(QMessageBox::NoIcon, "Cut", "Do you want to cut down this area?", QMessageBox::Yes | QMessageBox::No, NULL);
    if(message.exec() == QMessageBox::Yes)
    {
        //Rect roi(10, 20, 100, 50);
        image[currentstep+1] = image[currentstep](Range(begin_pointY,end_pointY), Range(begin_pointX,end_pointX)).clone();
        currentstep++;
        frame_load(image[currentstep]);
    }
    else
        frame_update(image[currentstep]);

}



