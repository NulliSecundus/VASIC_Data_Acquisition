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
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QWindow>
#include <QIcon>
#include <QDebug>

QT_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);

    ui->controllerStatus->setReadOnly(true);
    ui->controllerStatus->setAlignment(Qt::AlignCenter);
    ui->usingPortDisp->setAlignment(Qt::AlignCenter);
    ui->usingPortDisp->setReadOnly(true);
    ui->timeLineEdit->setReadOnly(true);
    ui->dateLineEdit->setReadOnly(true);
    ui->avgTimeWindow->setReadOnly(true);
    ui->fileNameWindow->setReadOnly(true);
    ui->field4Meas->setReadOnly(true);
    ui->field5Meas->setReadOnly(true);

    //setup for sensorOnBox checkbox
    ui->sensorOnBox->setChecked(false);
    ui->sensorOnBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->sensorOnBox->setFocusPolicy(Qt::NoFocus);

    //setup for dataSavingBox checkbox
    ui->dataSavingBox->setChecked(false);
    ui->dataSavingBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->dataSavingBox->setFocusPolicy(Qt::NoFocus);

    //setup for leftReceivingBox checkbox
    ui->leftReceivingBox->setChecked(false);
    ui->leftReceivingBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->leftReceivingBox->setFocusPolicy(Qt::NoFocus);

    //setup for rightReceivingBox checkbox
    ui->rightReceivingBox->setChecked(false);
    ui->rightReceivingBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->rightReceivingBox->setFocusPolicy(Qt::NoFocus);

    serial = new QSerialPort(this);
    selectPort = new SettingsDialog;
    t = new taredialog();
    calibrateWindow = new CalibrationWindow();
    timeSelect = new AvgTimeSelection();
    bytesToRead = 512;
    mode = "main";
    fileExtension = ".csv";

    time = QDateTime::currentDateTime();
    font = ui->timeLineEdit->font();
    font.setPointSize(10);
    ui->timeLineEdit->setFont(font);
    curTime = time.time().toString();
    ui->timeLineEdit->setText(curTime);
    ui->dateLineEdit->setFont(font);
    curDate = time.date().toString("MM-dd-yyyy");
    ui->dateLineEdit->setText(curDate);
    ui->lineEdit_3->setPlaceholderText("Name");
    ui->option1Line->setPlaceholderText("label 1");
    ui->option2Line->setPlaceholderText("label 2");

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

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitButton_clicked()
{
    QCoreApplication::quit();
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    QString s = data;
    if(s.contains("t")){
        mode = "timeMode";
    }else if(s.contains("z")){
        mode = "tareMode";
    }else if(s.contains("p")){
        mode = "calibrationMode";
    }else if(s.contains("m")){
        mode = "collectionMode";
        QMessageBox::information(this, "Success", "Controller responded OK");
        ui->controllerStatus->setText("Session Started");
        dataRead = false;
        writeStartSession();
    }else if(s.contains("k")){
        mode = "main";
        QMessageBox::information(this, "Success", "Controller responded OK");
    }
    processData(data, mode);
}

void MainWindow::processData(QByteArray data, QString mode){
    if(mode.compare("timeMode") == 0){
        if(QString(data).contains("g")){
            QMessageBox::information(timeSelect, "Success", "Time Mode Set");
        }
    }else if(mode.compare("collectionMode") == 0){
        if(data[0] == 'L'){
            procData = data;
        }else if(data.contains('V')){
            ui->sensorOnBox->setChecked(true);
            ui->controllerStatus->setText("Sensor Broken");
            dataRead = true;
            writeSensorBroken();
        }else if(data.contains('W')){
            ui->sensorOnBox->setChecked(false);
            ui->leftReceivingBox->setChecked(false);
            ui->rightReceivingBox->setChecked(false);
            ui->dataSavingBox->setChecked(false);
            ui->controllerStatus->setText("Waiting for Sensor Break");
            dataRead = false;
            writeSensorMade();
        }else if((data[data.length()-1] == '\r') && dataRead){
            procData.append(data);
            if(procData.contains('L') && procData.contains('R')){
                splitProc = procData.split('\r');
                if(splitProc.length() >= 2){
                    QByteArray leftData = splitProc.at(0);
                    QByteArray rightData = splitProc.at(1);
                    ui->leftReceivingBox->setChecked(true);
                    ui->rightReceivingBox->setChecked(true);
                    ui->dataSavingBox->setChecked(true);
                    ui->controllerStatus->setText("Averaging and Saving Data");
                    ui->field4Meas->setText(leftData.remove(0, 1));
                    ui->field5Meas->setText(rightData.remove(0,1));
                    writeDataToFile(leftData, rightData);
                }
            }
        }
        else{
            procData.append(data);
        }
    }else if(mode.compare("tareMode") == 0){
        if(data[0] == 'a'){
            QMessageBox::information(t, tr("Success"), "Left Side Tared");
        }else if(data[0] == 'b'){
            QMessageBox::information(t, tr("Success"), "Right Side Tared");
        }
    }
}

void MainWindow::on_calibrateButton_clicked()
{
    auto toWrite = "*P\\";
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
        writeData("*A\\");
    }else{
        writeData("*B\\");
    }
}

void MainWindow::onCalibrationEmpty()
{
    writeData("*C\\");
}

void MainWindow::onCalibrationTestWeight()
{
    writeData("*D\\");
}

void MainWindow::onCalibrationComplete()
{
    QString toWrite = "*S" + calibrateWindow->testWeightValue + "\\";
    writeData(toWrite.toLocal8Bit());
}

void MainWindow::onCalibrateClose()
{
    toWrite("*Q\\");
    mode = "main";
}

void MainWindow::on_tareButton_clicked()
{
    auto toWrite = "*Z\\";
    if (serial->isWritable()) {
        writeData(toWrite);
        t->show();
    } else {
        QMessageBox::critical(this, tr("Error"), "Unable to connect to device");
    }
}

void MainWindow::onTareClose()
{
    writeData("*Q\\");
    mode = "main";
}

void MainWindow::onLeftTare()
{
    writeData("*A\\");
}

void MainWindow::onRightTare()
{
    writeData("*B\\");
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
    auto toWrite = "*T\\";
    if (serial->isWritable()) {
        writeData(toWrite);
        timeSelect->show();
    } else {
        QMessageBox::critical(this, tr("Error"), "Unable to connect to device");
    }
}

void MainWindow::onAvgTimeSelected(int time, QString text)
{
    QString s = "*G" + QString::number(time) + "\\";
    ui->avgTimeWindow->setText(text);
    writeData(s.toLocal8Bit());
}

void MainWindow::onAvgTimeClose()
{
    writeData("*X\\");
    mode = "main";
}

void MainWindow::on_sessionStartButton_clicked()
{
    if((serial->isWritable()) && (filename.length()>0)){
        writeData("*M\\");
    }else if(!(serial->isWritable())){
        QMessageBox::critical(this, tr("Error"), "Unable to connect to device");
    }else if(filename.length() == 0){
        QMessageBox::critical(this, tr("Error"), "Please select a file to write to");
    }else{
        QMessageBox::critical(this, tr("Error"), "Unknown Error");
    }
}

void MainWindow::on_sessionStopButton_clicked()
{
    writeData("*K\\");
    mode = "main";
    ui->controllerStatus->setText("Session Ended");
    ui->field4Meas->clear();
    ui->field5Meas->clear();
    writeStopSession();
}

void MainWindow::on_selectFileButton_clicked()
{
    if(ui->radioButton_3->isChecked()){
        filename = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("Text Files (*.txt)"));
        directory.clear();
        ui->fileNameWindow->setText(filename);
    }else{
        filename = QFileDialog::getSaveFileName(this, tr("Save File"), QString(), tr("CSV Files (*.csv)"));
        directory.clear();
        ui->fileNameWindow->setText(filename);
    }
}

void MainWindow::on_defaultFilename_clicked()
{
    autoFileName();
    ui->fileNameWindow->setText(directory + filename);
}

void MainWindow::autoFileName()
{
    if(nameField.length()<1){
        nameField = "Name";
    }
    if(option1.length()>0 && option2.length()>0){
        filename = curDate + "_" + nameField + "_" + option1 + "_" + option2 + fileExtension;
    }else if(option1.length()>0){
        filename = curDate + "_" + nameField + "_" + option1 + fileExtension;
    }else if(option2.length()>0){
        filename = curDate + "_" + nameField + "_" + option2 + fileExtension;
    }else{
        filename = curDate + "_" + nameField + fileExtension;
    }
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    nameField = arg1;
}

void MainWindow::on_option1Line_textChanged(const QString &arg1)
{
    option1 = arg1;
}

void MainWindow::on_option2Line_textChanged(const QString &arg1)
{
    option2 = arg1;
}

void MainWindow::on_clearButton_clicked()
{
    ui->lineEdit_3->clear();
    ui->option1Line->clear();
    ui->option2Line->clear();
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if(checked){
        fileExtension = ".txt";
    }
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if(checked){
        fileExtension = ".csv";
    }
}

void MainWindow::on_selectFolderButton_clicked()
{
    directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    directory = directory + "/";
    autoFileName();
    ui->fileNameWindow->setText(directory + filename);
}

void MainWindow::writeStartSession()
{
    data.setFileName(directory + filename);
    if (data.open(QIODevice::WriteOnly| QIODevice::Truncate)) {
        QTextStream out(&data);
        out << "Time" << "," << "break" << "," << "Start/Stop" << "," << "TimeStamp" << "," << "break" << "," << "Left" << "," << "break" << "," << "Right" << "," << "Duration" << "\n";
        out << time.currentDateTime().time().toString() << "," << "*****" <<  "," << "Started Session" << "," << "*****" << "\n";
        data.close();
    }
}

void MainWindow::writeSensorBroken()
{
    timePrev = QDateTime::currentDateTime();
    if (data.open(QIODevice::ReadWrite| QIODevice::Append)) {
        QTextStream out(&data);
        out << time.currentDateTime().time().toString() << "," << "*****" <<  "," << "Sensor Broken" << "," << "*****" << "\n";
        data.close();
    }
}

void MainWindow::writeSensorMade()
{
    if (data.open(QIODevice::ReadWrite| QIODevice::Append)) {
        QTextStream out(&data);
        out << time.currentDateTime().time().toString() << "," << "*****" <<  "," << "Sensor Made" << "," << "*****" << "\n";
        data.close();
    }
}

void MainWindow::writeStopSession()
{
    if (data.open(QIODevice::ReadWrite| QIODevice::Append)) {
        QTextStream out(&data);
        out << time.currentDateTime().time().toString() << "," << "*****" <<  "," << "Stopped Session" << "," << "*****" << "\n";
        data.close();
    }
}

void MainWindow::writeDataToFile(QByteArray left, QByteArray right)
{
    if (data.open(QIODevice::ReadWrite| QIODevice::Append)) {
        QTextStream out(&data);
        timeCur = QDateTime::currentDateTime();
        qint64 ref = timePrev.msecsTo(timeCur);
        double refSec = double(ref) / double(1000);
        out << "," << "," << "," << time.currentDateTime().time().toString() << "," << "," << left << "," << "," << right << "," << refSec << "\n";
        data.close();
    }
}
