#ifndef TAREDIALOG_H
#define TAREDIALOG_H

#include <QDialog>

namespace Ui {
class taredialog;
}

class taredialog : public QDialog
{
    Q_OBJECT

public:
    explicit taredialog(QWidget *parent = 0);
    ~taredialog();

signals:
    void tareClose();

private slots:

    void on_tareExitButton_clicked();

    void on_tareButton_clicked();

private:
    Ui::taredialog *ui;
};

#endif // TAREDIALOG_H
