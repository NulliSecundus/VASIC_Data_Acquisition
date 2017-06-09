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

    auto layout = new QVBoxLayout;
    horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));

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
        layout->addWidget(label);
        layout->addWidget(button1);
        layout->setAlignment(button1, Qt::AlignRight);
    }
    horizontalGroupBox->setLayout(layout);
    const auto workPage = new QWidget;
    workPage->setLayout(layout);

    mainLayout->addWidget(workPage);

    setLayout(mainLayout);
    setWindowTitle(tr("Basic Layouts"));

    workPage->show();

    //    QScrollArea area;
    //    area.setWindowTitle(QObject::tr("Info about all available serial ports."));
    //    area.setWidget(workPage);
    //    area.show();
}

SelectPort::~SelectPort()
{
    delete ui;
}
