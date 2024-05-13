#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    COMPORT = new QSerialPort;
    COMPORT->setPortName("COM5");
    COMPORT->setBaudRate(QSerialPort::BaudRate::Baud9600);
    COMPORT->setParity(QSerialPort::Parity::NoParity);
    COMPORT->setDataBits(QSerialPort::DataBits::Data8);
    COMPORT->setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    COMPORT->open(QIODevice::ReadWrite);

    if(COMPORT->isOpen()){
        qDebug() << "Serial port is connected";
        qDebug() << COMPORT->error();
    }
    else{
        qDebug() << "Serial port is not connect.";
        qDebug() << COMPORT->error();
    }

    connect(COMPORT, SIGNAL(readyRead()), this, SLOT(Read_Data()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSend_clicked()
{
    if(COMPORT->isOpen()){
        // char(10) = \n;
        // char(13) = \r;
        COMPORT->write(ui->lineEdit_Serial_Data->text().toUtf8() + char(10));
        COMPORT->flush();
    }
}

void MainWindow::Read_Data()
{
    if(COMPORT->isOpen()){
        while(COMPORT->bytesAvailable()){
            Data_From_SerialPort += COMPORT->readAll();
            if(Data_From_SerialPort.at(Data_From_SerialPort.length() - 1) == char(10)){
                Is_Data_Received = true;
            }
        }
        if(Is_Data_Received == true){
            qDebug() << "Data From Serial Port: " << Data_From_SerialPort;
            ui->txtReceivedData->append(Data_From_SerialPort);
            Data_From_SerialPort = "";
            Is_Data_Received = false;
        }
    }
}
