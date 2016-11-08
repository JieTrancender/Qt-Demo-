#include "widget.h"
#include "ui_widget.h"
#include <QMouseEvent>

Widget::Widget(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::open()
{
    setWindowModality(Qt::WindowModal);
    show();
}

void Widget::exec()
{
    setAttribute(Qt::WA_ShowModal, true);
    show();
    QEventLoop loop;
    loop.exec();
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    ui->pushButton->setText(tr("%1, %2").arg(e->x()).arg(e->y()));
}
