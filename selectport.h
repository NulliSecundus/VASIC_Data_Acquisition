#ifndef SELECTPORT_H
#define SELECTPORT_H

#include <QDialog>
#include <QListWidget>

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

private:
    Ui::SelectPort *ui;
};

#endif // SELECTPORT_H
