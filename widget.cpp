#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList serialNamePort;
    foreach(const QSerialPortInfo& info, QSerialPortInfo::availablePorts()){
        serialNamePort << info.portName();
    }
    ui->ckh->addItems(serialNamePort);

    serialPort = new QSerialPort(this);
    connect(serialPort,&QSerialPort::readyRead,this,&Widget::on_read_receive);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_dkck_clicked()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity parity;

//    if(ui->btl->currentText() == "4800"){
//        baudRate = QSerialPort::Baud4800;
//    }else if(ui->btl->currentText() == "9600"){
//        baudRate = QSerialPort::Baud9600;
//    }else if(ui->btl->currentText() == "115200"){
//        baudRate = QSerialPort::Baud115200;
//    }

    switch (ui->btl->currentIndex()) {
        case 0:
            baudRate = QSerialPort::Baud4800;
            break;
        case 1:
            baudRate = QSerialPort::Baud9600;
            break;
        case 2:
            baudRate = QSerialPort::Baud115200;
            break;
    }

    switch (ui->sjw->currentIndex()) {
        case 0:
            dataBits = QSerialPort::Data5;
            break;
        case 1:
            dataBits = QSerialPort::Data6;
            break;
        case 2:
            dataBits = QSerialPort::Data7;
            break;
        case 3:
            dataBits = QSerialPort::Data8;
            break;
    }

    switch (ui->tzw->currentIndex()) {
        case 0:
            stopBits = QSerialPort::OneStop;
            break;
        case 1:
            stopBits = QSerialPort::OneAndHalfStop;
            break;
        case 2:
            stopBits = QSerialPort::TwoStop;
            break;
    }

    if(ui->jyw->currentText() == "none"){
        parity = QSerialPort::NoParity;
    }
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);
    serialPort->setParity(parity);
    serialPort->setPortName(ui->ckh->currentText());

    if(serialPort->open(QIODevice::ReadWrite) == true){
        QMessageBox::information(this,"提示","成功");
    }else{
        QMessageBox::critical(this,"提示","失败");
    }
}

void Widget::on_gbck_clicked()
{
    serialPort->close();
}

void Widget::on_read_receive()
{
    QString buf;
    buf = serialPort->readAll();
    ui->plainTextEdit->appendPlainText(buf);
}

void Widget::on_fsck_clicked()
{
    serialPort->write(ui->lineEdit->text().toLocal8Bit().data());
}

void Widget::on_qkck_clicked()
{
    ui->plainTextEdit->clear();
}
