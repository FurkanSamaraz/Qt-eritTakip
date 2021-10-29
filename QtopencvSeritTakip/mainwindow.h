#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <QImage>
#include <vector>
#include <iostream>
#include <QTimer>

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_on_pushButton_open_webcam_clicked();

    void on_on_pushButton_close_webcam_clicked();
    void guncelle_windows();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    VideoCapture cap;
     Mat frame;
     QImage qt_image;
     std::vector<cv::Rect> plaka;
     CascadeClassifier yuz;

};
#endif // MAINWINDOW_H
