#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "photo_frame.h"

using namespace std;
using namespace cv;

Mat image[100];
int currentstep=0;

String face_cascade_name = "C://opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "C://opencv/sources/data/lbpcascades/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;

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
    //-- 1. Load the cascade
    if(!face_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml") )
        ui->label_2->setText("--(!)Error loading face cascade\n");

    if(!eyes_cascade.load("C:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml") )
        ui->label_2->setText("--(!)Error loading eyes cascade\n");



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


    QMessageBox message(QMessageBox::NoIcon, "Save", "Do you want to save photo?", QMessageBox::Yes | QMessageBox::No, NULL);
    if(message.exec() == QMessageBox::Yes)
    {
        if(!image[currentstep].empty()){
            QString Simgpath=QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("PNG(*.png);;JPG(*.jpg)"));
            if(!Simgpath.isNull()){
                imwrite(Simgpath.toStdString(),image[currentstep]);
            }
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
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
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

        //求X方向梯度
        Sobel( image[currentstep], grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
        convertScaleAbs( grad_x, abs_grad_x );
        //求Y方向梯度
        Sobel( image[currentstep], grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
        convertScaleAbs( grad_y, abs_grad_y );
        //合併梯度(近似)
        addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, image[currentstep+1] );
        currentstep++;
        break;
    case 3:
        detectAndDisplay(image[0]);
        break;
    default:
        break;
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

void MainWindow::detectAndDisplay(Mat frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(10, 10) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;

        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    //imshow( "window_name", frame );
    image[currentstep+1]=frame.clone();
    currentstep++;
    /*photo_window_update(image[currentstep],0);
    un_redo();*/
}
