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
    QString testWeightValue;

private slots:
    void on_calibrationExitButton_clicked();

    void on_calibrationStartButton_clicked();

    void on_readEmptyWeightButton_clicked();

    void on_readTestWeightButton_clicked();

    void on_sendTestWeightButton_clicked();

    void on_LeftLCButton_toggled(bool checked);

    void on_RightLCButton_toggled(bool checked);

    void on_testWeightValue_textEdited(const QString &arg1);

private:
    Ui::CalibrationWindow *ui;
    bool left;
    bool right;
    bool startCalibration;

signals:
    void onCalibrationClose();
    void calibrationStart(bool left);
    void emptyWeightRead();
    void testWeightRead();
    void testWeightSent();
};

#endif // CALIBRATIONWINDOW_H
