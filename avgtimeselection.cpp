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
