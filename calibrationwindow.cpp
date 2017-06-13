#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"

CalibrationWindow::CalibrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
}

CalibrationWindow::~CalibrationWindow()
{
    delete ui;
}

void CalibrationWindow::on_calibrationExitButton_clicked()
{
    emit onCalibrationClose();
    this -> close();
}



void CalibrationWindow::on_calibrationStartButton_clicked()
{

}

void CalibrationWindow::on_readEmptyWeightButton_clicked()
{

}

void CalibrationWindow::on_readTestWeightButton_clicked()
{

}

void CalibrationWindow::on_sendTestWeightButton_clicked()
{

}
