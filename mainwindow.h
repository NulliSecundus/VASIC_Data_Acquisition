/****************************************************************************
**
** VASIC Data Acquisition GUI - a VASIC GUI created using the Qt framework
**
** Copyright (C) (2018) Yang Laboratory, University of Wisconsin - Madison
**
** Distributed under the GNU Public License (GPL)
** See the file 'COPYING' for details
**
** Author: Brendan Drackley
** Email: brendandrackley@gmail.com
**
** Please send bug reports to: jyang75@wisc.edu
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

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
#include <QFile>

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
    QDateTime timePrev;
    QDateTime timeCur;
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
    QFile data;
    bool dataRead;
    bool sessionRunning;
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
