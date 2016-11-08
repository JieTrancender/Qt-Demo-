#include "eventdialog.h"
#include "ui_eventdialog.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QDateTime>

EventDialog::EventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventDialog)
{
    ui->setupUi(this);
    id1 = startTimer(1000);
    id2 = startTimer(2000);
    id3 = startTimer(10000);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(timerUpdate()));
    timer->start(1000);
}

EventDialog::~EventDialog()
{
    delete ui;
}

void EventDialog::mousePressEvent(QMouseEvent *event)
{
    ui->pushButton->setText(tr("(%1, %2)").arg(event->x()).arg(event->y()));
}

void EventDialog::keyPressEvent(QKeyEvent *event)
{
    int x = ui->pushButton->x();
    int y = ui->pushButton->y();

    switch (event->key())
    {
    case Qt::Key_W : ui->pushButton->move(x, y - 10); break;
    case Qt::Key_S : ui->pushButton->move(x, y + 10); break;
    case Qt::Key_A : ui->pushButton->move(x - 10, y); break;
    case Qt::Key_D : ui->pushButton->move(x + 10, y); break;
    }
}

void EventDialog::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == id1)
    {
        ui->label->setText(tr("%1").arg(qrand() % 10));
    }
    else if (event->timerId() == id2)
    {
        ui->label_2->setText(tr("Hello World!"));
    }
    else
    {
        qApp->quit();
    }
}

void EventDialog::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->lineEdit->setText(str);
}
