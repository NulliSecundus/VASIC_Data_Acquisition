#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationwindow.h"
#include "taredialog.h"
#include "selectport.h"
#include "settingsdialog.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

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
    ui->controllerStatus->setAlignment(Qt::AlignCenter);
    ui->usingPortDisp->setAlignment(Qt::AlignCenter);
    ui->usingPortDisp->setReadOnly(true);

    serial = new QSerialPort(this);
    selectPort = new SettingsDialog;

    connect(selectPort, SIGNAL(updatePort()), this, SLOT(openSerialPort()));
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
    closeSerialPort();
    selectPort->show();
}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings portSettings = selectPort->settings();
    serial->setPortName(portSettings.name);
    serial->setBaudRate(portSettings.baudRate);
    serial->setDataBits(portSettings.dataBits);
    serial->setParity(portSettings.parity);
    serial->setStopBits(portSettings.stopBits);
    serial->setFlowControl(portSettings.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        ui->usingPortDisp->setText(serial->portName());
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen()){
        serial->close();
    }
}
