#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationwindow.h"
#include "taredialog.h"
#include "settingsdialog.h"
#include "avgtimeselection.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDateTime>

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
    ui->timeLineEdit->setReadOnly(true);
    ui->dateLineEdit->setReadOnly(true);
    ui->avgTimeWindow->setReadOnly(true);
    ui->fileNameWindow->setReadOnly(true);

    serial = new QSerialPort(this);
    selectPort = new SettingsDialog;
    t = new taredialog();
    calibrateWindow = new CalibrationWindow();
    timeSelect = new AvgTimeSelection();

    time = QDateTime::currentDateTime();
    font = ui->timeLineEdit->font();
    font.setPointSize(10);
    ui->timeLineEdit->setFont(font);
    ui->timeLineEdit->setText(time.time().toString());
    ui->dateLineEdit->setFont(font);
    ui->dateLineEdit->setText(time.date().toString("MM-dd-yyyy"));

    connect(selectPort, SIGNAL(updatePort()), this, SLOT(openSerialPort()));
    connect(t, &taredialog::tareClose, this, &MainWindow::onTareClose);
    connect(t, &taredialog::leftTareClick, this, &MainWindow::onLeftTare);
    connect(t, &taredialog::rightTareClick, this, &MainWindow::onRightTare);

    connect(calibrateWindow, &CalibrationWindow::onCalibrationClose, this, &MainWindow::onCalibrateClose);
    connect(calibrateWindow, &CalibrationWindow::calibrationStart, this, &MainWindow::onCalibrationStart);
    connect(calibrateWindow, &CalibrationWindow::emptyWeightRead, this, &MainWindow::onCalibrationEmpty);
    connect(calibrateWindow, &CalibrationWindow::testWeightRead, this, &MainWindow::onCalibrationTestWeight);
    connect(calibrateWindow, &CalibrationWindow::testWeightSent, this, &MainWindow::onCalibrationComplete);

    connect(timeSelect, &AvgTimeSelection::avgTimeSelected, this, &MainWindow::onAvgTimeSelected);
    connect(timeSelect, &AvgTimeSelection::avgTimeClose, this, &MainWindow::onAvgTimeClose);
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

void MainWindow::onCalibrationStart(bool left)
{
    if(left){
        writeData("*A//");
    }else{
        writeData("*B//");
    }
}

void MainWindow::onCalibrationEmpty()
{
    writeData("*C//");
}

void MainWindow::onCalibrationTestWeight()
{
    writeData("*D//");
}

void MainWindow::onCalibrationComplete()
{
    QString toWrite = "*S" + calibrateWindow->testWeightValue + "//";
    writeData(toWrite.toLocal8Bit());
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

void MainWindow::on_updateTime_clicked()
{
    time = QDateTime::currentDateTime();
    ui->timeLineEdit->setText(time.time().toString());
    ui->dateLineEdit->setText(time.date().toString("MM-dd-yyyy"));
}

void MainWindow::on_selectTimeButton_clicked()
{
    auto toWrite = "*T//";
    if (serial->isWritable()) {
        writeData(toWrite);
        timeSelect->show();
    } else {
        QMessageBox::critical(this, tr("Error"), "Unable to connect to device");
    }
}

void MainWindow::onAvgTimeSelected(int time, QString text)
{
    QString s = "*G" + QString::number(time) + "//";
    ui->avgTimeWindow->setText(text);
    writeData(s.toLocal8Bit());
}

void MainWindow::onAvgTimeClose()
{
    writeData("*X//");
}
