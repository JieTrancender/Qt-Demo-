#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //painter.drawLine(QPointF(0, 0), QPointF(100, 100));
    /*QPen pen;
    pen.setColor(QColor(255, 0, 0));
    QBrush brush(QColor(0, 255, 0, 125));
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(50, 50, 200, 100);*/

    /*QPen pen(Qt::DotLine);
    QBrush brush(Qt::blue);
    brush.setStyle(Qt::HorPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(50, 50 ,200, 200);

    QRectF rectangle(10, 20, 80, 60);
    int startAngle = 30 * 16;
    int spanAngle = 120 * 16;
    painter.drawArc(rectangle, startAngle, spanAngle);

    QLinearGradient linearGradient(QPointF(40, 190), QPointF(70, 190));
    linearGradient.setColorAt(0, Qt::yellow);
    linearGradient.setColorAt(0.5, Qt::red);
    linearGradient.setColorAt(1, Qt::green);

    linearGradient.setSpread(QGradient::RepeatSpread);

    painter.setBrush(linearGradient);
    painter.drawRect(10, 20, 90, 40);

    QRadialGradient radialGradient(QPointF(100, 190),50,QPointF(275,200));
    radialGradient.setColorAt(0, QColor(255, 255, 100, 150));
    radialGradient.setColorAt(1, QColor(0, 0, 0, 50));
    painter.setBrush(radialGradient);
    painter.drawEllipse(QPointF(100, 190), 50, 50);

    QConicalGradient conicalGradient(QPointF(250, 190), 60);
    conicalGradient.setColorAt(0.2, Qt::cyan);
    conicalGradient.setColorAt(0.9, Qt::black);
    painter.setBrush(conicalGradient);
    painter.drawEllipse(QPointF(250, 190), 50, 50);*/

    /*QFont font("宋体", 15, QFont::Bold, true);
    font.setUnderline(true);
    font.setOverline(true);
    font.setCapitalization(QFont::SmallCaps);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 1);

    painter.setFont(font);
    painter.drawText(100, 100, "jie-email@jie-trancender.org");
    QRectF rect(20, 20, 300, 200);
    painter.drawRect(rect);
    painter.setPen(QColor(Qt::red));
    painter.drawText(rect, Qt::AlignHCenter, "Hello, World!");*/

    /*QPainterPath path;
    path.addEllipse(100, 100, 50, 50);
    path.lineTo(200, 200);

    painter.setPen(Qt::blue);
    painter.setBrush(Qt::red);
    painter.drawPath(path);

    QPainterPath path2;
    path2.addPath(path);
    path2.translate(100,0);
    painter.drawPath(path2);*/

    QPainterPath path;
        path.addRect(50, 50, 40, 40);
        //移动到(100, 100)点
        path.moveTo(100, 100);
        path.lineTo(200, 200);
        //QPainter painter(this);
        painter.drawPath(path);
}
