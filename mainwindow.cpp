#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTime>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,timer(new QTimer(this))
{
    ui->setupUi(this);
    this->initializeSerialPort();
    this->startListenerGate();
    this->ui->pushButtonClear->setDisabled(true);
    QObject::connect(&mSerialInput, SIGNAL(readyRead()), this,SLOT(readDataInput()));
//    QObject::connect(&mSerialOutput, SIGNAL(readyRead()), this,SLOT(readDataOutput()));
    QObject::connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(clearAll()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));

}
void MainWindow::startListenerGate()
{
    if (mSerialInput.open(QIODevice::ReadWrite)) {

    } else {
        QMessageBox::critical(this, tr("Error"), mSerialInput.errorString());
        exit(1);
    }
}

void MainWindow::initializeSerialPort()
{
    mSerialInput.setPortName("ttyACM0");
//    mSerialInput.open(QIODevice::WriteOnly);
    mSerialInput.setBaudRate(9600);
//    mSerialInput.setDataBits(QSerialPort::Data8);
//    mSerialInput.setParity(QSerialPort::NoParity);
//    mSerialInput.setStopBits(QSerialPort::OneStop);
//    mSerialInput.setFlowControl(QSerialPort::NoFlowControl);

}
void MainWindow::closeSerialPort()
{
    if (mSerialInput.isOpen())
        mSerialInput.close();
}
void MainWindow::writeDataInput(const QByteArray &data)
{
    mSerialInput.write(data);
}

void MainWindow::clearAll()
{
    time=new QTime(0,0);
    this->ui->lcdNumberMiliSec->display(0);
    this->ui->lcdNumberSec->display(0);
    this->ui->lcdNumberMin->display(0);
    this->ui->lcdNumberHours->display(0);
}
void MainWindow::readDataInput()
{
    const QByteArray data = mSerialInput.readAll();
    qDebug()<<data;
    if (data=="1"){
//        qDebug()<<data;
        this->ui->pushButtonClear->setDisabled(true);
        time=new QTime(0,0);
        this->timer->start(10);
    }else if(data=="0"){
        qDebug()<<data;
        timer->stop();
        this->ui->pushButtonClear->setEnabled(true);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerHit()
{
    *time=time->addMSecs(10);
    this->ui->lcdNumberMiliSec->display(time->msec());
    this->ui->lcdNumberSec->display(time->second());
    if(time->minute()>0){
        this->ui->lcdNumberMin->display(time->minute());
        if(time->hour()>0){
            this->ui->lcdNumberMin->display(time->hour());
        }
    }
}

