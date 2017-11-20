/*
許述文 20170731
學習QImage、read TXT file、tab的使用，以及圖片灰階處理
想把圖片處理做成一個function,還沒成功
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowTitle(tr("GrayScale"));


    this->setFixedSize(1000,600);
    /*this->setStyleSheet(
                "background-image:url(https://up-1.cdn-fullscreendirect.com/production/photos/10393/large/20170214_211843_10393_968993.jpeg);background-position: center;");*/



    //QPixmap使用底層平台的繪製系統進行繪製，無法提供像素級別的操作，而QImage則是獨立於硬體的繪製系統，
    //因此可以用setPixel()函式，對影像的像素進行設置，且QImage在不同系統上有相同的影像。
    //bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);


    /*  QPalette palette;   //調色盤
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
*/




    undo_redo_enable();             //每執行一次修改偵測一次有沒有復原和重做
    //設置滑動條控件的最小值
    ui->BrightnessSlider->setMinimum(-60);
    //設置滑動條控件的最大值
    ui->BrightnessSlider->setMaximum(60);
    //設置滑動條控件的值
    ui->BrightnessSlider->setValue(0);

    ui->warmSlider->setMinimum(-50);
    ui->warmSlider->setMaximum(50);
    ui->warmSlider->setValue(0);

    ui->saturation_slider->setValue(0);
    ui->saturation_slider->setMaximum(50);
    ui->saturation_slider->setMinimum(-50);

    ui->greybtn->setEnabled(false);
    ui->BrightnessSlider->setEnabled(false);
    ui->brightnessset_btn->setEnabled(false);
    ui->warmSlider->setEnabled(false);
    ui->saturation_slider->setEnabled(false);
    ui->warmset_btn->setEnabled(false);
    ui->saturation_btn->setEnabled(false);
    ui->blur->setEnabled(false);
    ui->Sharpen->setEnabled(false);
}

void MainWindow::undo_redo_enable(){

    if(currentstep>0)
        ui->actionUndo->setEnabled(true);
    else
        ui->actionUndo->setEnabled(false);

    if(Image[currentstep+1]!=NULL)
        ui->actionRedo->setEnabled(true);
    else
        ui->actionRedo->setEnabled(false);

}


MainWindow::~MainWindow()
{
    delete ui;
    delete []*Image;
}


//-----------------------------------圖片處理區


QImage *MainWindow::greyScale(QImage *origin){
    QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

    QColor oldColor;

    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(origin->pixel(x,y));
            int average = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            newImage->setPixel(x,y,qRgb(average,average,average));
        }
    }

    return newImage;
}


QImage *MainWindow::brightnessScale(bool set, int value, QImage *origin){
    QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

    QColor oldColor;

    for(int x = 0; x<newImage->width(); x++){
        for(int y = 0; y<newImage->height(); y++){
            oldColor = QColor(origin->pixel(x,y));
            if(oldColor.red()+value>=0&&oldColor.red()+value<=255&&
                    oldColor.green()+value>=0&&oldColor.green()+value<=255&&
                    oldColor.blue()+value>=0&&oldColor.blue()+value<=255)
            {
                newImage->setPixel(x,y,qRgb(oldColor.red()+value,oldColor.green()+value,oldColor.blue()+value));

            }
            else
                newImage->setPixel(x,y,qRgb(oldColor.red(),oldColor.green(),oldColor.blue()));
        }
    }

    if(set==0){
        pixmap = QPixmap::fromImage(*newImage);
        ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    }

    else if(set==1)
        return newImage;
}

QImage * MainWindow::warm(bool set, int value, QImage * origin){
    QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);
    QColor oldColor;
    int r,g,b;
    if(value>=0){
        for(int x=0; x<newImage->width(); x++){
            for(int y=0; y<newImage->height(); y++){
                oldColor = QColor(origin->pixel(x,y));

                r = oldColor.red() + value;
                g = oldColor.green() + value;
                b = oldColor.blue();
                //we check if the new values are between 0 and 255

                r = qBound(0, r, 255);  // a given object's value by given minimum and maximum values using the qBound() function.
                g = qBound(0, g, 255);


                newImage->setPixel(x,y, qRgb(r,g,b));
            }
        }
    }
    else if(value<0){
        value=-value;
        for(int x=0; x<newImage->width(); x++){

            for(int y=0; y<newImage->height(); y++){

                oldColor = QColor(origin->pixel(x,y));

                r = oldColor.red();
                g = oldColor.green();
                b = oldColor.blue()+value;

                //we check if the new value is between 0 and 255

                b = qBound(0, b, 255);
                newImage->setPixel(x,y, qRgb(r,g,b));
            }
        }
    }
    if(set==0){
        pixmap = QPixmap::fromImage(*newImage);
        ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    }

    else if(set==1)
        return newImage;
}


QImage * MainWindow::saturation(bool set, int value, QImage *origin){
    QImage * newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

    QColor oldColor;
    QColor newColor;
    int h,s,l;

    for(int x=0; x<newImage->width(); x++){
        for(int y=0; y<newImage->height(); y++){
            oldColor = QColor(origin->pixel(x,y));

            newColor = oldColor.toHsl();
            h = newColor.hue();
            s = newColor.saturation()+value;
            l = newColor.lightness();

            //we check if the new value is between 0 and 255
            s = qBound(0, s, 255);

            newColor.setHsl(h, s, l);

            newImage->setPixel(x, y, qRgb(newColor.red(), newColor.green(), newColor.blue()));
        }
    }
    if(set==0){
        pixmap = QPixmap::fromImage(*newImage);
        ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    }

    else if(set==1)
        return newImage;
}

QImage * MainWindow::blur(QImage * origin){
    QImage * newImage = new QImage(*origin);

    int kernel [5][5]= {{0,0,1,0,0},
                        {0,1,3,1,0},
                        {1,3,7,3,1},
                        {0,1,3,1,0},
                        {0,0,1,0,0}};
    int kernelSize = 5;
    int sumKernel = 27;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(origin->pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));

        }
    }
    return newImage;
}

QImage * MainWindow::sharpen(QImage * origin){
    QImage * newImage = new QImage(* origin);

    int kernel [3][3]= {{0,-1,0},
                        {-1,5,-1},
                        {0,-1,0}};
    int kernelSize = 3;
    int sumKernel = 1;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(origin->pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));

        }
    }
    return newImage;
}


//------------------------------------互動按鈕區



//slider

void MainWindow::on_BrightnessSlider_valueChanged(int value){

    ui->sliderlabel->setText(QString::number(value));
    brightnessdelta=value;
    brightnessScale(0,brightnessdelta,Image[currentstep]);

}

void MainWindow::on_warmSlider_valueChanged(int value){
    ui->sliderlabel_warm->setText(QString::number(value));
    color_temperaturedelta=value;
    warm(0,color_temperaturedelta,Image[currentstep]);

}

void MainWindow::on_saturation_slider_valueChanged(int value)
{
    ui->sliderlabel_saturation->setText(QString::number(value));
    saturationdelta=value;
    saturation(0,saturationdelta,Image[currentstep]);

}
//button

void MainWindow::on_greybtn_clicked()

{
    Image[currentstep+1]=greyScale(Image[currentstep]);
    pixmap = QPixmap::fromImage(*Image[currentstep+1]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));

    currentstep++;

    undo_redo_enable();
}

void MainWindow::on_brightnessset_btn_clicked()

{

    Image[currentstep+1]=brightnessScale(1,brightnessdelta,Image[currentstep]);
    pixmap = QPixmap::fromImage(*Image[currentstep+1]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));

    currentstep++;

    undo_redo_enable();

}

void MainWindow::on_warmset_btn_clicked()

{

    Image[currentstep+1]=warm(1,color_temperaturedelta,Image[currentstep]);
    pixmap = QPixmap::fromImage(*Image[currentstep+1]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    currentstep++;

    undo_redo_enable();

}

void MainWindow::on_saturation_btn_clicked()
{
    Image[currentstep+1]=saturation(1,saturationdelta,Image[currentstep]);
    pixmap = QPixmap::fromImage(*Image[currentstep+1]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    currentstep++;

    undo_redo_enable();
}

//navbar
void MainWindow::on_actionOpen_File_triggered()
{

    for(int i=0;i<100;i++)
    {Image[i]={NULL};}            //每開一次新檔重置一次
    *Image=new QImage;            //宣告整個指標陣列都是QImage?
    currentstep=0;

    //開啟路徑
    QString imgpath=QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("Image *.png *.jpg"));
    Image[0]->load(imgpath);

    //載入圖片到lable
    pixmap = QPixmap::fromImage(*Image[0]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));

    ui->greybtn->setEnabled(true);
    ui->BrightnessSlider->setEnabled(true);
    ui->brightnessset_btn->setEnabled(true);
    ui->warmSlider->setEnabled(true);
    ui->warmset_btn->setEnabled(true);
    ui->saturation_btn->setEnabled(true);
    ui->saturation_slider->setEnabled(true);
    ui->blur->setEnabled(true);
    ui->Sharpen->setEnabled(true);
    ui->saturation_slider->setEnabled(true);
    undo_redo_enable();
}

void MainWindow::on_actionSave_File_triggered()
{
    if(Image[currentstep]==NULL){
        QMessageBox msgBox;
        msgBox.setText("The image hasn't been loaded.");
        msgBox.exec();

    }

    else{
        QString Simgpath=QFileDialog::getSaveFileName(this, tr("Save File"),"/",tr("PNG(*.png);;JPG(*.jpg)"));
        *Image[currentstep]=pixmap.toImage();
        Image[currentstep]->save(Simgpath);
    }
}

void MainWindow::on_actionUndo_triggered()
{

    currentstep--;

    pixmap = QPixmap::fromImage(*Image[currentstep]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    undo_redo_enable();
}

void MainWindow::on_actionRedo_triggered()
{

    currentstep++;

    pixmap = QPixmap::fromImage(*Image[currentstep]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));

    undo_redo_enable();
}

void MainWindow::on_blur_clicked()
{
    Image[currentstep+1]=blur(Image[currentstep]);
    pixmap = QPixmap::fromImage(*Image[currentstep+1]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    currentstep++;

    undo_redo_enable();
}

void MainWindow::on_Sharpen_clicked()
{
    Image[currentstep+1]=sharpen(Image[currentstep]);
    pixmap = QPixmap::fromImage(*Image[currentstep+1]);
    ui->label->setPixmap(pixmap.scaled(ui->label->width(),ui->label->height()));
    currentstep++;

    undo_redo_enable();
}

