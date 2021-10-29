#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::guncelle_windows()
{
    cap >> frame; //Kamerayı frameye atama
    //cap.read(frame);
   // cv::Mat grey_image;
    cvtColor(frame, frame, CV_BGR2RGB);
    //cv::equalizeHist(frame, frame);
    yuz.load("C:/OpencvQTt/opencv-3.4.3/source/data/haarcascades/haarcascade_frontalface_default.xml");

   yuz.detectMultiScale(frame, plaka, 1.1, 2,  0|CV_HAAR_SCALE_IMAGE,
                                 cv::Size(frame.cols/4, frame.rows/4)); // Minimum size of obj

    for( size_t i = 0; i < plaka.size(); i++)
    {
        cap.retrieve(frame);

        cv::rectangle(frame, plaka[i], cv::Scalar( 100, 50, 190 ),3);

       cv::putText(frame, "Plaka", Point(10, 15), FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(90, 44, 255),2);

         }



    for( size_t i = 0; i < plaka.size(); i++)
    {
        cap.retrieve(frame);

        cv::rectangle(frame, plaka[i], cv::Scalar( 100, 50, 190 ),3);

       cv::putText(frame, "Plaka", Point(10, 15), FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(90, 44, 255),2);

         }


    qt_image = QImage((const unsigned char*)(frame.data),frame.cols,frame.rows,QImage::Format_RGB888); //sütün ve satır

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());


}


void MainWindow::on_on_pushButton_open_webcam_clicked()
{
    cap.open(0);  //0. kamerayı aç
    if(!cap.isOpened())
    {
        cout<<"Kamera Acilmadi!"<<endl;

    }
    else
    {
        cout<<"Kamera Acildi."<<endl;

    connect(timer,SIGNAL(timeout()),this,SLOT(guncelle_windows())); //QTimer fonksiyonu ile eklediğimiz guncelle_window slotuna atadık.
    timer->start(20); //Tepki süresini 20 saniye olarak ayarladık.
}
}


void MainWindow::on_on_pushButton_close_webcam_clicked()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(guncelle_windows())); //Bağlantıyı kesmek için
    cap.release();

    Mat image = Mat::zeros(frame.size(),CV_8UC3);// 8 Bitlik 3 kanallı
    qt_image = QImage((const unsigned char*)(image.data),image.cols,image.rows,QImage::Format_RGB888); //sütün ve satır

    ui->label->setPixmap(QPixmap::fromImage(qt_image)); //label atama
    ui->label->resize(ui->label->pixmap()->size());

    cout<<"Kamera Kapandı."<<endl;

}

