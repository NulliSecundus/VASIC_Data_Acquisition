#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationwindow.h"
#include "taredialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    this->statusBar()->setSizeGripEnabled(false);
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
