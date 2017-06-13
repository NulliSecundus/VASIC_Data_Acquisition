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
    void leftTareClick();
    void rightTareClick();

private slots:

    void on_tareExitButton_clicked();

    void on_tareButton_clicked();

    void on_LeftLCButton_toggled(bool checked);

    void on_RightLCButton_toggled(bool checked);

private:
    Ui::taredialog *ui;
    bool left;
    bool right;
};

#endif // TAREDIALOG_H
