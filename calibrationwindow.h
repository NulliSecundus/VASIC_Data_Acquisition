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

#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H


#include <QMainWindow>
#include <QDialog>

namespace Ui {
class CalibrationWindow;
}

class CalibrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CalibrationWindow(QWidget *parent = 0);
    ~CalibrationWindow();
    QString testWeightValue;

private slots:
    void on_calibrationExitButton_clicked();

    void on_calibrationStartButton_clicked();

    void on_readEmptyWeightButton_clicked();

    void on_readTestWeightButton_clicked();

    void on_sendTestWeightButton_clicked();

    void on_LeftLCButton_toggled(bool checked);

    void on_RightLCButton_toggled(bool checked);

    void on_testWeightValue_textEdited(const QString &arg1);

private:
    Ui::CalibrationWindow *ui;
    bool left;
    bool right;
    bool startCalibration;

signals:
    void onCalibrationClose();
    void calibrationStart(bool left);
    void emptyWeightRead();
    void testWeightRead();
    void testWeightSent();
};

#endif // CALIBRATIONWINDOW_H
