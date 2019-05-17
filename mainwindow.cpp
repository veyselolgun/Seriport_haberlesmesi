#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort>
#include<QString>
#include <QSerialPortInfo>
#include<QComboBox>
#include <QSerialPortInfo>
#include<QMessageBox>
#include<QByteArray>



QSerialPort *serialport_okuma;

QSerialPort MainWindow::serialport_yazma;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);

    serialport_okuma= new QSerialPort(this);


    for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
    {

        ui->combobox_okuma_portu_sec->addItem(port.portName());
        ui->combobox_yazma_portunu_sec->addItem(port.portName());
    }
    connect(serialport_okuma,SIGNAL(readyRead()),this,SLOT(serialport_read()));
        
    connect(ui->buton_veriyi_gonder,SIGNAL(clicked(bool)),this,SLOT(serialport_read()));

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::serialport_read()

{
    // seriport üzerinden gönderilen veriler dinlenir ve plaintext içine yazılır
    ui->plainTextEdit->insertPlainText(serialport_okuma->readAll().toHex());
}


void MainWindow::on_buton_yazmaportunu_kapa_clicked()
{
    ui->buton_yazma_portunu_ac->setText("yazma portunu ac");
    ui->buton_yazma_portunu_ac->setStyleSheet("color: black;"
                                              "background-color:grey");
    serialport_yazma.close();
}

void MainWindow::on_buton_okuma_portunu_kapat_clicked()
{
    ui->buton_okuma_portunu_ac->setText("okuma portunu ac");

    ui->buton_okuma_portunu_ac->setStyleSheet("color: black;"
                                              "background-color:grey");

    serialport_okuma->close();
}

void MainWindow::on_buton_okuma_portunu_ac_clicked()
{

    serialport_okuma->setPortName(ui->combobox_okuma_portu_sec->currentText());
    serialport_okuma->setBaudRate(9600);


    if(serialport_okuma->open(QIODevice::ReadWrite))

    {
        ui->buton_okuma_portunu_ac->setStyleSheet("color:green;");
        ui->buton_okuma_portunu_ac ->setText("okuma portu acik");
    }

    else

    {

        ui->buton_okuma_portunu_ac->setStyleSheet("color:black;"
                                                  "background-color:red");
        ui->buton_okuma_portunu_ac->setText(" okuma portu acilamadi ");

    }
}

void MainWindow::on_buton_yazma_portunu_ac_clicked()
{
    serialport_yazma.setPortName(ui->combobox_yazma_portunu_sec->currentText());
    serialport_yazma.setBaudRate(9600);


    if(serialport_yazma.open(QIODevice::ReadWrite))

    {


        ui->buton_yazma_portunu_ac->setStyleSheet("color:green;");
        ui->buton_yazma_portunu_ac->setText("yazma portu acik  ");

    }

    else

    {     ui->buton_yazma_portunu_ac->setStyleSheet("color:black;"
                                                    "background-color:red");
        ui->buton_yazma_portunu_ac->setText("yazma portu acilamadi");


    }
}

void MainWindow::on_buton_veriyi_gonder_clicked()
{
    if(!serialport_yazma.isOpen())

    { QMessageBox::critical(this,"title","yazma portunu aciniz");

    }

    serialport_yazma.write(ui->lineEdit_text_veri->text().toStdString().data());

}
