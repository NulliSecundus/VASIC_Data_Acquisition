#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"

CalibrationWindow::CalibrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    left = false;
    right = false;
    startCalibration = false;
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
    if(left){
        emit calibrationStart(true);
        startCalibration = true;
    }else if(right){
        emit calibrationStart(false);
        startCalibration = true;
    }else{
        //Message: please select a load cell to calibrate
    }
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

void CalibrationWindow::on_LeftLCButton_toggled(bool checked)
{
    if(checked){
        left = true;
    }else{
        left = false;
    }
}

void CalibrationWindow::on_RightLCButton_toggled(bool checked)
{
    if(checked){
        right = true;
    }else{
        right = false;
    }
}
