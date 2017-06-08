#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationwindow.h"
#include "taredialog.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort>
#include <QSerialPortInfo>

QT_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
    ui->controllerStatus->setReadOnly(true);
    ui->controllerStatus->setText("Displaying Raw Data");

    auto layout = new QVBoxLayout;

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QString s = QObject::tr("Port: ") + info.portName() + "\n"
                + QObject::tr("Location: ") + info.systemLocation() + "\n"
                + QObject::tr("Description: ") + info.description() + "\n"
                + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
                + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
                + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";

        auto label = new QLabel(s);
        layout->addWidget(label);
    }
    const auto workPage = new QWidget;
    workPage->setLayout(layout);

    area.setWindowTitle(QObject::tr("Info about all available serial ports."));
    area.setWidget(workPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::on_calibrateButton_clicked()
{
    calibrateWindow = new CalibrationWindow();
    calibrateWindow->show();
}

void MainWindow::on_tareButton_clicked()
{
    t = new taredialog();
    t->show();
}

void MainWindow::on_portSelectButton_clicked()
{
    area.show();
}
