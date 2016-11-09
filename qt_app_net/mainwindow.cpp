#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    ui->progressBar->hide();

    //manager = new QNetworkAccessManager(this);
    //关联管理器的finished信号和自定义槽
    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    //manager->get(QNetworkRequest(QUrl("http://www.qter.org")));
    //manager->get(QNetworkRequest(QUrl("http://www.jie-trancender.org")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::httpFinished()
{
    ui->progressBar->hide();
    file->flush();
    file->close();
    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void MainWindow::updateDataReadProgress(qint64 bytesRead, qint64 totalBytes)
{
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesRead);
}

void MainWindow::startRequest(QUrl url)
{
    reply = manager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDataReadProgress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

/*void MainWindow::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf");
    QString all = codec->toUnicode(reply->readAll());  //QNetworkReply继承自QIODevice类
    ui->textBrowser->setText(all);
    reply->deleteLater();
}*/

void MainWindow::on_pushButton_clicked()
{
    url = ui->lineEdit->text();
    QFileInfo info(url.path());
    QString fileName(info.fileName());
    if (fileName.isEmpty())
    {
        fileName ="index.html";
    }
    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly))
    {
        qDebug() << "file open error";
        delete file;
        file = 0;
        return;
    }
    startRequest(url);
    ui->progressBar->setValue(0);
    ui->progressBar->show();
}

void MainWindow::httpReadyRead()
{
    if (file)
    {
        file->write(reply->readAll());
    }
}
