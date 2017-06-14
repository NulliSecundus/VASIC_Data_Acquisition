#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taredialog.h"
#include "calibrationwindow.h"
#include "settingsdialog.h"
#include "avgtimeselection.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>

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
    void onCalibrationStart(bool left);
    void onCalibrationEmpty();
    void onCalibrationTestWeight();
    void onCalibrationComplete();

    void on_tareButton_clicked();
    void onTareClose();
    void onLeftTare();
    void onRightTare();

    void on_portSelectButton_clicked();

    void openSerialPort();

    void on_updateTime_clicked();

    void on_selectTimeButton_clicked();
    void onAvgTimeSelected(int time, QString text);
    void onAvgTimeClose();

private:
    Ui::MainWindow *ui;
    taredialog *t;
    CalibrationWindow *calibrateWindow;
    SettingsDialog *selectPort;
    QDateTime time;
    QFont font;
    AvgTimeSelection *timeSelect;
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void toWrite(const QByteArray &data);
};

#endif // MAINWINDOW_H
