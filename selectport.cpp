#include "selectport.h"
#include "ui_selectport.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QGroupBox>
#include <QPushButton>
#include <QtWidgets>

QGroupBox *horizontalGroupBox;

SelectPort::SelectPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPort)
{
    ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLabel *titleLine = new QLabel;
    titleLine->setText("Please select the comm port in use: ");
    mainLayout->addWidget(titleLine);
    mainLayout->setAlignment(titleLine, Qt::AlignTop);

    auto layout2 = new QVBoxLayout;

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QString s = QObject::tr("Port: ") + info.portName() + "\n"
                //                + QObject::tr("Location: ") + info.systemLocation() + "\n"
                + QObject::tr("Description: ") + info.description() + "\n"
                //                + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                //                + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                //                + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                //                + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";

        auto label = new QLabel(s);
        QPushButton *button1 = new QPushButton("Select Port", this);
        auto layout = new QHBoxLayout;
        layout->addWidget(label);
        layout->addWidget(button1);
        layout2->addLayout(layout);
        layout2->setAlignment(layout, Qt::AlignTop);
    }
    const auto workPage = new QWidget;
    workPage->setLayout(layout2);

    mainLayout->addWidget(workPage);
    mainLayout->setAlignment(workPage, Qt::AlignTop);

    setLayout(mainLayout);
    setWindowTitle(tr("Basic Layouts"));

    workPage->show();
}

SelectPort::~SelectPort()
{
    delete ui;
}
