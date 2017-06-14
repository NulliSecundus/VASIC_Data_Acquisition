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
        QMessageBox::information(this, tr("Success"), "Left Side Tared");
        emit leftTareClick();
    }else if(right){
        QMessageBox::information(this, tr("Success"), "Right Side Tared");
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
