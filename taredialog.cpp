#include "taredialog.h"
#include "ui_taredialog.h"

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
