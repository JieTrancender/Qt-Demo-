#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("new windows");
    dlg = new QDialog(this);

    QAction *openAction = new QAction(tr("&Open"), this);
    QIcon icon(":/images/li.jpg");
    openAction->setIcon(icon);

    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    ui->menu_F->addAction(openAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //dlg = new QDialog(this);
    dlg->show();
}
