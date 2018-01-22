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

#include "taredialog.h"
#include "ui_taredialog.h"
#include <QMessageBox>

taredialog::taredialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taredialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    left = false;
    right = false;
}

taredialog::~taredialog()
{
    delete ui;
}

void taredialog::on_tareExitButton_clicked()
{
    emit tareClose();
    this -> close();
}

void taredialog::on_tareButton_clicked()
{
    if(left){
        emit leftTareClick();
    }else if(right){
        emit rightTareClick();
    }else{
        //Message: please select a load cell to Tare
        QMessageBox::critical(this, tr("Error"), "Please Select a Load Cell");
    }
}

void taredialog::on_LeftLCButton_toggled(bool checked)
{
    if(checked){
        left = true;
    }else{
        left = false;
    }
}

void taredialog::on_RightLCButton_toggled(bool checked)
{
    if(checked){
        right = true;
    }else{
        right = false;
    }
}
