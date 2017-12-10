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
    //image[0]=imread("D://Photos/BB8/BB8.jpg");
    //image[0]=imread("D://Photos/BB8/15609246_1219648224796806_584233906_o.jpg");
    //cvtColor(image,image,CV_RGB2BGR);
    //imshow("new",image[0]);

    un_redo();

    ui->brightness_slider->setMinimum(-10);
    ui->brightness_slider->setMaximum(10);

    ui->contrast_slider->setMinimum(-10);
    ui->contrast_slider->setMaximum(10);

    ui->brightness_slider->setValue(0);
    ui->contrast_slider->setValue(0);


    myTimer = new QTimer(this);
    myTimer->start(500);                   //以1000毫秒為週期起動定時器
    connect(myTimer,SIGNAL(timeout()),this,SLOT(un_redo()));
}


MainWindow::~MainWindow()
{
    if(!image[currentstep].empty()){
        QString Simgpath=QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("PNG(*.png);;JPG(*.jpg)"));
        if(!Simgpath.isNull()){
            imwrite(Simgpath.toStdString(),image[currentstep]);
        }
    }
    for(int i=0;i<100;i++){
        image[i].release();
    }

    delete ui;
}

void MainWindow::photo_window_update(Mat frame,int r){


    static photo_frame P_frame;

    P_frame.frame_update(frame);
    P_frame.show();
    if(r==1){
        P_frame.frame_load(frame);

    }
    else if(r==0){
        P_frame.frame_update(frame);
    }

}
void MainWindow::on_blur_btn_clicked()
{

    GaussianBlur(image[currentstep],image[currentstep+1],Size(9,9),0,0);
    currentstep++;
    photo_window_update(image[currentstep],0);
    un_redo();
}


void MainWindow::un_redo(){
    if(image[currentstep].empty()){
        ui->blur_btn->setEnabled(false);
        ui->brightness_slider->setEnabled(false);
        ui->contrast_slider->setEnabled(false);
        ui->magicbox->setEnabled(false);
        ui->magic_set_btn->setEnabled(false);
        ui->set_bright_btn->setEnabled(false);
        ui->set_con_btn->setEnabled(false);
        ui->shapen_btn->setEnabled(false);
    }
    else{
        ui->blur_btn->setEnabled(true);
        ui->brightness_slider->setEnabled(true);
        ui->contrast_slider->setEnabled(true);
        ui->magicbox->setEnabled(true);
        ui->magic_set_btn->setEnabled(true);
        ui->set_bright_btn->setEnabled(true);
        ui->set_con_btn->setEnabled(true);
        ui->shapen_btn->setEnabled(true);

    }

    if(currentstep>0)
        ui->actionUndo->setEnabled(true);
    else
        ui->actionUndo->setEnabled(false);

    if(!image[currentstep+1].empty())
        ui->actionRedo->setEnabled(true);
    else
        ui->actionRedo->setEnabled(false);
    ui->label->setText("Step: "+QString::number(currentstep));
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Select an Image"),"/home","Images(*.png *.bmp *.jpg)");
    if(!filename.isNull()){
        for(int i=0;i<100;i++){
            image[i].release();
        }
        image[0]=imread(filename.toStdString());
        currentstep=0;
        photo_window_update(image[currentstep],1);
        un_redo();
    }

}


void MainWindow::on_actionUndo_triggered()
{
    //image[0]=imread("D://Photos/BB8/15609246_1219648224796806_584233906_o.jpg");
    currentstep--;
    un_redo();
    photo_window_update(image[currentstep],0);
}

void MainWindow::on_actionRedo_triggered()
{
    //image[0]=imread("D://Photos/BB8/BB8.jpg");
    currentstep++;
    un_redo();
    photo_window_update(image[currentstep],0);
}

void MainWindow::on_actionSave_File_triggered()
{
    if(image[currentstep].empty()){
        QMessageBox msgBox;
        msgBox.setText("No flie loaded");
        msgBox.exec();

    }

    else{
        QString Simgpath=QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("PNG(*.png);;JPG(*.jpg)"));
        if(!Simgpath.isNull()){
            imwrite(Simgpath.toStdString(),image[currentstep]);
        }
    }
}

void MainWindow::on_shapen_btn_clicked()
{
    Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    filter2D(image[currentstep], image[currentstep+1], image[currentstep].depth(), kernel);
    //Laplacian(image[currentstep],image[currentstep+1],image[currentstep].type());
    currentstep++;

    photo_window_update(image[currentstep],0);
    un_redo();
}



void MainWindow::on_magic_set_btn_clicked()
{
    int index;

    index= ui->magicbox->currentIndex();

    switch(index){
    case 0:
        if(image[currentstep].channels()!=1){
            cvtColor(image[currentstep],image[currentstep+1], COLOR_BGR2GRAY,1);
            currentstep++;
        }
        break;
    case 1:
        if(image[currentstep].channels()==1){

            equalizeHist(image[currentstep],image[currentstep+1]);
            currentstep++;
        }
        else{
            //msg=new QMessageBox(this);
            QMessageBox::about(NULL,"Attention","Convert to gray image first.");
        }
        break;
    case 2:
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;
        //求X方向梯度
        Sobel( image[currentstep], grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );
        //求Y方向梯度
        Sobel( image[currentstep], grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );
        //合併梯度(近似)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, image[currentstep+1] );
        currentstep++;
    }


    //ui->magic_set_btn->setText(QString::number(index));


    photo_window_update(image[currentstep],0);
    un_redo();
}


void MainWindow::on_contrast_slider_sliderReleased()
{
    int value=ui->contrast_slider->value();
    double alpha=double(value+10)/10;
    int beta=0;
    Mat preview;
    image[currentstep].convertTo(preview, -1, alpha, beta);

    photo_window_update(preview,0);
    un_redo();
}


void MainWindow::on_brightness_slider_sliderReleased()
{
    int value=ui->brightness_slider->value();
    double alpha=1;
    int beta=value*5;
    Mat preview;
    image[currentstep].convertTo(preview, -1, alpha, beta);

    photo_window_update(preview,0);
    un_redo();
}



void MainWindow::on_set_bright_btn_clicked()
{
    int value=ui->brightness_slider->value();
    double alpha=1;
    int beta=value*5;
    image[currentstep].convertTo(image[currentstep+1], -1, alpha, beta);
    currentstep++;


    photo_window_update(image[currentstep],0);
    un_redo();
    ui->brightness_slider->setValue(0);


}

void MainWindow::on_set_con_btn_clicked()
{
    int value=ui->contrast_slider->value();
    double alpha=double(value+10)/10;
    int beta=0;

    image[currentstep].convertTo(image[currentstep+1], -1, alpha, beta);
    currentstep++;

    photo_window_update(image[currentstep],0);
    un_redo();
    ui->contrast_slider->setValue(0);
}
