#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taredialog.h"
#include "calibrationwindow.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitButton_clicked();

    void on_calibrateButton_clicked();

    void on_tareButton_clicked();

    void on_portSelectButton_clicked();

private:
    Ui::MainWindow *ui;
    taredialog *t;
    CalibrationWindow *calibrateWindow;
    QScrollArea area;
};

#endif // MAINWINDOW_H
