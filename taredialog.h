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

#ifndef TAREDIALOG_H
#define TAREDIALOG_H

#include <QDialog>

namespace Ui {
class taredialog;
}

class taredialog : public QDialog
{
    Q_OBJECT

public:
    explicit taredialog(QWidget *parent = 0);
    ~taredialog();

signals:
    void tareClose();
    void leftTareClick();
    void rightTareClick();

private slots:

    void on_tareExitButton_clicked();

    void on_tareButton_clicked();

    void on_LeftLCButton_toggled(bool checked);

    void on_RightLCButton_toggled(bool checked);

private:
    Ui::taredialog *ui;
    bool left;
    bool right;
};

#endif // TAREDIALOG_H
