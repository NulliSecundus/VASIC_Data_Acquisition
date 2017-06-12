#ifndef SELECTPORT_H
#define SELECTPORT_H

#include <QDialog>
#include <QListWidget>
#include <QtSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class SelectPort;
}

class SelectPort : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPort(QWidget *parent = 0);
    ~SelectPort();

private slots:
    void onExitButtonClicked();
    void onSelectPortClicked();

private:
    Ui::SelectPort *ui;
};

#endif // SELECTPORT_H
