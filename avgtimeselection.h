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

#ifndef AVGTIMESELECTION_H
#define AVGTIMESELECTION_H

#include <QDialog>

namespace Ui {
class AvgTimeSelection;
}

class AvgTimeSelection : public QDialog
{
    Q_OBJECT

public:
    explicit AvgTimeSelection(QWidget *parent = 0);
    ~AvgTimeSelection();

private slots:
    void on_AvgTimeComboBox_activated(int index);

    void on_OK_button_clicked();

    void on_AvgTimeComboBox_activated(const QString &arg1);

    void on_sendButton_clicked();

    void on_defaultButton_clicked();

private:
    Ui::AvgTimeSelection *ui;
    int avgTime;
    QString avgTimeText;

signals:
    void avgTimeSelected(int time, QString text);
    void avgTimeClose();
};

#endif // AVGTIMESELECTION_H
