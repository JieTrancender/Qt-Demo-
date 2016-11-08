#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>

namespace Ui {
class EventDialog;
}

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventDialog(QWidget *parent = 0);
    ~EventDialog();

protected:
    void mousePressEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void timerEvent(QTimerEvent *event);

private slots:
    void timerUpdate();

private:
    Ui::EventDialog *ui;

    int id1, id2, id3, id4;
};

#endif // EVENTDIALOG_H
