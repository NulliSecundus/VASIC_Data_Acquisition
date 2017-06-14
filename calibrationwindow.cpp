#include "calibrationwindow.h"
#include "ui_calibrationwindow.h"
#include <QMessageBox>

CalibrationWindow::CalibrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    left = false;
    right = false;
    startCalibration = false;
    CalibrationWindow::testWeightValue = "200.00";

    //setup for calibrationStart checkbox
    ui->CalibrationStart->setChecked(false);
    ui->CalibrationStart->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->CalibrationStart->setFocusPolicy(Qt::NoFocus);

    //setup for EmptyWeightRec checkbox
    ui->EmptyWeightRec->setChecked(false);
    ui->EmptyWeightRec->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->EmptyWeightRec->setFocusPolicy(Qt::NoFocus);

    //setup for TestWeightRec checkbox
    ui->TestWeightRec->setChecked(false);
    ui->TestWeightRec->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->TestWeightRec->setFocusPolicy(Qt::NoFocus);

    //setup for CalibrationComplete checkbox
    ui->CalibrationComplete->setChecked(false);
    ui->CalibrationComplete->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->CalibrationComplete->setFocusPolicy(Qt::NoFocus);

    QDoubleValidator *d = new QDoubleValidator(this);
    ui->testWeightValue->setValidator(d);
}

CalibrationWindow::~CalibrationWindow()
{
    delete ui;
}

void CalibrationWindow::on_calibrationExitButton_clicked()
{
    ui->CalibrationStart->setChecked(false);
    ui->EmptyWeightRec->setChecked(false);
    ui->TestWeightRec->setChecked(false);
    ui->CalibrationComplete->setChecked(false);
    emit onCalibrationClose();
    this -> close();
}



void CalibrationWindow::on_calibrationStartButton_clicked()
{
    if(left){
        emit calibrationStart(true);
        startCalibration = true;
        ui->CalibrationStart->setChecked(true);
        ui->EmptyWeightRec->setChecked(false);
        ui->TestWeightRec->setChecked(false);
        ui->CalibrationComplete->setChecked(false);
    }else if(right){
        emit calibrationStart(false);
        startCalibration = true;
        ui->CalibrationStart->setChecked(true);
        ui->EmptyWeightRec->setChecked(false);
        ui->TestWeightRec->setChecked(false);
        ui->CalibrationComplete->setChecked(false);
    }else{
        //Message: please select a load cell to calibrate
        QMessageBox::critical(this, tr("Error"), "Please Select a Load Cell");
    }
}

void CalibrationWindow::on_readEmptyWeightButton_clicked()
{
    if(startCalibration){
        emit emptyWeightRead();
        ui->EmptyWeightRec->setChecked(true);
    }
}

void CalibrationWindow::on_readTestWeightButton_clicked()
{
    if(startCalibration){
        emit testWeightRead();
        ui->TestWeightRec->setChecked(true);
    }
}

void CalibrationWindow::on_sendTestWeightButton_clicked()
{
    if(startCalibration){
        emit testWeightSent();
        ui->CalibrationComplete->setChecked(true);
    }
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

void CalibrationWindow::on_testWeightValue_textEdited(const QString &arg1)
{
    testWeightValue = arg1;
}
