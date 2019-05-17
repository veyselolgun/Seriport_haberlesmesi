#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     static QSerialPort serialport_yazma;



private slots:

     void serialport_read();

     void on_buton_yazmaportunu_kapa_clicked();

     void on_buton_okuma_portunu_kapat_clicked();

     void on_buton_okuma_portunu_ac_clicked();

     void on_buton_yazma_portunu_ac_clicked();

     void on_buton_veriyi_gonder_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
