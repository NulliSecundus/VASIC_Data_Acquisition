#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H


#include <QMainWindow>
#include <QDialog>

namespace Ui {
    class CalibrationWindow;
}

class CalibrationWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit CalibrationWindow(QWidget *parent = 0);
        ~CalibrationWindow();

private slots:
    void on_calibrationExitButton_clicked();

private:
        Ui::CalibrationWindow *ui;
};

#endif // CALIBRATIONWINDOW_H
