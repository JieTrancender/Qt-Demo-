#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    loadSize = 4 * 1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
    tcpSocket = new QTcpSocket(this);

    //一旦链接服务器成功，就传送文件
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(startTransfer()));

    //当有数据发送成功时，更新进度条
    connect(tcpSocket, SIGNAL(bytesWritten(qint64)),this, SLOT(updateClientProgress(qint64)));

    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    //开始发送按钮不可用
    ui->sendButton->setEnabled(false);

   // connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::send()
{
    ui->sendButton->setEnabled(false);
    bytesWritten = 0;
    ui->clientStatusLabel->setText(tr("connecting..."));
    tcpSocket->connectToHost(ui->hostLineEdit->text(), ui->portLineEdit->text().toInt());
}

void Widget::startTransfer()
{
    localFile = new QFile(fileName);
    if (!localFile->open(QFile::ReadOnly))
    {
        qDebug() << "Open file error";
        return;
    }

    totalBytes = localFile->size();

    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_6);
    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);

    //一次写入总大小信息，文件名大小，文件名
    sendOut << qint64(0) << qint64(0) << currentFileName;

    totalBytes += outBlock.size();

    sendOut.device()->seek(0);

    sendOut << totalBytes << qint64((outBlock.size() - sizeof(qint64) * 2));

    bytesToWrite = totalBytes - tcpSocket->write(outBlock);
    ui->clientStatusLabel->setText("connected...");
    outBlock.resize(0);
}

void Widget::updateClientProgress(qint64 numBytes)
{
    bytesWritten += (int)numBytes;

    if (bytesToWrite > 0)
    {
        outBlock = localFile->read(qMin(bytesToWrite, loadSize));
        bytesToWrite -= (int)tcpSocket->write(outBlock);

        outBlock.resize(0);
    }
    else
    {
        localFile->close();
    }

    ui->clientProgressBar->setMaximum(totalBytes);
    ui->clientProgressBar->setValue(bytesWritten);

    if (bytesToWrite == totalBytes)
    {
        ui->clientStatusLabel->setText(tr("发送文件 %1 成功").arg(fileName));
        localFile->close();
        tcpSocket->close();
    }
}



void Widget::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpSocket->errorString();
    tcpSocket->close();
    ui->clientProgressBar->reset();
    ui->clientStatusLabel->setText("client is ok");
    ui->sendButton->setEnabled(true);
}

void Widget::openFile()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        ui->sendButton->setEnabled(true);
        ui->clientStatusLabel->setText(tr("打开文件 %1 成功").arg(fileName));
    }
}

void Widget::on_openButton_clicked()
{
    openFile();
}

void Widget::on_sendButton_clicked()
{
    send();
}
