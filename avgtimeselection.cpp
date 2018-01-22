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

#include "avgtimeselection.h"
#include "ui_avgtimeselection.h"
#include <QMessageBox>

AvgTimeSelection::AvgTimeSelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvgTimeSelection)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->AvgTimeComboBox->insertItem(0,"0.5 Second");
    ui->AvgTimeComboBox->insertItem(1,"1.0 Second");
    ui->AvgTimeComboBox->insertItem(2,"1.5 Second");
    ui->AvgTimeComboBox->insertItem(3,"2.0 Second");
    ui->AvgTimeComboBox->insertItem(4,"2.5 Second");
    ui->AvgTimeComboBox->insertItem(5,"3.0 Second");
    ui->AvgTimeComboBox->insertItem(6,"3.5 Second");
    ui->AvgTimeComboBox->insertItem(7,"4.0 Second");
    ui->AvgTimeComboBox->insertItem(8,"4.5 Second");
    ui->AvgTimeComboBox->insertItem(9,"5.0 Second");

    avgTime = 1;
    avgTimeText = "1.0 Second";

}

AvgTimeSelection::~AvgTimeSelection()
{
    delete ui;
}

void AvgTimeSelection::on_AvgTimeComboBox_activated(int index)
{
    avgTime = index;
}

void AvgTimeSelection::on_OK_button_clicked()
{
    emit avgTimeClose();
    this->close();
}

void AvgTimeSelection::on_AvgTimeComboBox_activated(const QString &arg1)
{
    avgTimeText = arg1;
}

void AvgTimeSelection::on_sendButton_clicked()
{
    emit avgTimeSelected(avgTime, avgTimeText);
}

void AvgTimeSelection::on_defaultButton_clicked()
{
    avgTimeText = "1.0 Second";
    avgTime = 1;
    ui->AvgTimeComboBox->setCurrentIndex(1);
}
