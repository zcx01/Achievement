#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFile>
#include <QDebug>

#define YUVWI 1920
#define YUVHE 1080
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto t = new QTimer(this);
    auto f = new QFile("/home/chengxiongzhu/Works/Repos/changan_c835/ds.yuv",this);
    auto ba = new QByteArray(YUVWI*YUVHE*2,0);

    f->open(QIODevice::ReadOnly);
    qDebug(" c=%d",ba->count());
    connect(t,&QTimer::timeout,this,[=](){
        if(f->read(ba->data(),ba->count()) <=0){
            f->seek(0);
            if(f->read(ba->data(),ba->count()) <=0){
                qDebug("error again");
                t->stop();
                return;
            }
        }
        ui->centralwidget->slotShowYuv((uchar*)(ba->data()),YUVWI,YUVHE);
    });
    t->setInterval(40);
    t->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

