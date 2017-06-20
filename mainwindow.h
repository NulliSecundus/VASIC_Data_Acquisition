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

    void readData();

    void on_sessionStartButton_clicked();

    void on_sessionStopButton_clicked();

    void on_selectFileButton_clicked();

    void on_defaultFilename_clicked();

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_option1Line_textChanged(const QString &arg1);

    void on_option2Line_textChanged(const QString &arg1);

    void on_clearButton_clicked();

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_selectFolderButton_clicked();

private:
    Ui::MainWindow *ui;
    taredialog *t;
    CalibrationWindow *calibrateWindow;
    SettingsDialog *selectPort;
    QDateTime time;
    QFont font;
    AvgTimeSelection *timeSelect;
    QByteArray procData;
    QByteArray procLeft;
    QByteArray procRight;
    qint64 bytesRead;
    qint64 bytesToRead;
    QString mode;
    QList<QByteArray> splitProc;
    QString filename;
    QString curDate;
    QString curTime;
    QString nameField;
    QString option1;
    QString option2;
    QString fileExtension;
    QString directory;
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void toWrite(const QByteArray &data);
    void processData(QByteArray data, QString mode);
    void autoFileName();
    void writeStartSession();
    void writeSensorBroken();
    void writeSensorMade();
    void writeStopSession();
    void writeDataToFile(QByteArray left, QByteArray right);
};

#endif // MAINWINDOW_H
