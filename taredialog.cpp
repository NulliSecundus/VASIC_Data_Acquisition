#include "taredialog.h"
#include "ui_taredialog.h"

taredialog::taredialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::taredialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
}

taredialog::~taredialog()
{
    delete ui;
}

void taredialog::on_tareExitButton_clicked()
{
    this -> close();
}
