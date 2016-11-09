#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    totalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start()
{
    ui->startButton->setEnabled(false);
    bytesReceived = 0;
    if (!tcpServer->listen(QHostAddress::LocalHost, 6666))
    {
        qDebug() << tcpServer->errorString();
        close();
        return;
    }
    ui->serverStatusLabel->setText("Listening");
}

void Widget::acceptConnection()
{
    tcpServerConnection = tcpServer->nextPendingConnection();
    connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(updateServerProgress()));
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    ui->serverStatusLabel->setText("receive connection");
    tcpServer->close();
}

void Widget::updateServerConnection()
{
    QDataStream in(tcpServerConnection);
       in.setVersion(QDataStream::Qt_4_6);
       if(bytesReceived <= sizeof(qint64)*2)
       { //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息
           if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)
               && (fileNameSize == 0))
           { //接收数据总大小信息和文件名大小信息
               in >> totalBytes >> fileNameSize;
               bytesReceived += sizeof(qint64) * 2;
           }
           if((tcpServerConnection->bytesAvailable() >= fileNameSize)
               && (fileNameSize != 0))
           {  //接收文件名，并建立文件
               in >> fileName;
               ui->serverStatusLabel->setText(tr("接收文件 %1 ...")
                                               .arg(fileName));
               bytesReceived += fileNameSize;
               localFile= new QFile(fileName);
               if(!localFile->open(QFile::WriteOnly))
               {
                    qDebug() << "open file error!";
                    return;
               }
           }
           else return;
       }
       if(bytesReceived < totalBytes)
       {  //如果接收的数据小于总数据，那么写入文件
          bytesReceived += tcpServerConnection->bytesAvailable();
          inBlock= tcpServerConnection->readAll();
          localFile->write(inBlock);
          inBlock.resize(0);
       }
    //更新进度条
       ui->serverProgressBar->setMaximum(totalBytes);
       ui->serverProgressBar->setValue(bytesReceived);

       if(bytesReceived == totalBytes)
       { //接收数据完成时
        tcpServerConnection->close();
        localFile->close();
        ui->startButton->setEnabled(true);
    ui->serverStatusLabel->setText(tr("receive file %1 succes!")
    .arg(fileName));
       }

}

void Widget::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << tcpServerConnection->errorString();
       tcpServerConnection->close();
       ui->serverProgressBar->reset();
       ui->serverStatusLabel->setText(tr("server ready"));
       ui->startButton->setEnabled(true);
}


void Widget::on_startButton_clicked()
{
    start();
}
