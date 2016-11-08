#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "logindialog.h"
#include "eventdialog.h"
#include "widget.h"
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    /*MainWindow w;
    LoginDialog dlg;
    if (dlg.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }

    Widget *wid = new Widget;
    wid->show();*/

    EventDialog eventDlg;

    return eventDlg.exec();
}
