#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taredialog.h"
#include "calibrationwindow.h"
#include "selectport.h"
#include "settingsdialog.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSerialPort *serial;

private slots:
    void on_exitButton_clicked();

    void on_calibrateButton_clicked();
    void onCalibrateClose();

    void on_tareButton_clicked();
    void onTareClose();

    void on_portSelectButton_clicked();

    void openSerialPort();

private:
    Ui::MainWindow *ui;
    taredialog *t;
    CalibrationWindow *calibrateWindow;
    SettingsDialog *selectPort;
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void toWrite(const QByteArray &data);
};

#endif // MAINWINDOW_H
