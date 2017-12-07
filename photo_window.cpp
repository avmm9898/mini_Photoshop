#include "photo_window.h"
#include "ui_photo_window.h"

photo_window::photo_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::photo_window)
{
    ui->setupUi(this);
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(ui->label);
    ui->scrollAreaWidgetContents->setLayout(lay);
    frame_in();

}
void photo_window::frame_in(){
    int fix_image_height=800;
    Pixmap=QPixmap::fromImage(Mat2QImage(image));
    Pixmap=Pixmap.scaledToHeight(fix_image_height);
    int image_width=Pixmap.width();             //which is the width after scaled
    ui->label->setGeometry(0,0,image_width,fix_image_height);
    ui->label->setPixmap(Pixmap);
    this->setFixedSize(image_width+50,fix_image_height+50);
}
QImage photo_window::Mat2QImage(const Mat src){
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
photo_window::~photo_window()
{
    delete ui;
}
