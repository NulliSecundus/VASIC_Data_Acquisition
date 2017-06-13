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
    t = new taredialog();
    calibrateWindow = new CalibrationWindow();

    connect(selectPort, SIGNAL(updatePort()), this, SLOT(openSerialPort()));
    connect(t, &taredialog::tareClose, this, &MainWindow::onTareClose);
    connect(calibrateWindow, &CalibrationWindow::onCalibrationClose, this, &MainWindow::onCalibrateClose);
    connect(t, &taredialog::leftTareClick, this, &MainWindow::onLeftTare);
    connect(t, &taredialog::rightTareClick, this, &MainWindow::onRightTare);
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
    auto toWrite = "*P//";
    if (serial->isWritable()) {
        writeData(toWrite);
        calibrateWindow->show();
    } else {
        QMessageBox::critical(this, tr("Error"), "Unable to connect to device");
    }
}

void MainWindow::onCalibrateClose()
{
    toWrite("*Q//");
}

void MainWindow::on_tareButton_clicked()
{
    auto toWrite = "*Z//";
    if (serial->isWritable()) {
        writeData(toWrite);
        t->show();
    } else {
        QMessageBox::critical(this, tr("Error"), "Unable to connect to device");
    }
}

void MainWindow::onTareClose()
{
//    toWrite("*Q/");
    writeData("*Q//");
}

void MainWindow::onLeftTare()
{
    writeData("*A//");
}

void MainWindow::onRightTare()
{
    writeData("*B//");
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

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MainWindow::toWrite(const QByteArray &data)
{
    if (serial->isWritable()) {
        writeData(data);
    } else {
        QMessageBox::critical(this, tr("Error"), "Unable to connect to device");
    }
}
