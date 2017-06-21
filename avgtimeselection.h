#ifndef AVGTIMESELECTION_H
#define AVGTIMESELECTION_H

#include <QDialog>

namespace Ui {
class AvgTimeSelection;
}

class AvgTimeSelection : public QDialog
{
    Q_OBJECT

public:
    explicit AvgTimeSelection(QWidget *parent = 0);
    ~AvgTimeSelection();

private slots:
    void on_AvgTimeComboBox_activated(int index);

    void on_OK_button_clicked();

    void on_AvgTimeComboBox_activated(const QString &arg1);

    void on_sendButton_clicked();

    void on_defaultButton_clicked();

private:
    Ui::AvgTimeSelection *ui;
    int avgTime;
    QString avgTimeText;

signals:
    void avgTimeSelected(int time, QString text);
    void avgTimeClose();
};

#endif // AVGTIMESELECTION_H
