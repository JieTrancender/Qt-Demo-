#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_startButton_clicked();
    void start();
    void acceptConnection();
    void updateServerConnection();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    Ui::Widget *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpServerConnection;
    qint64 totalBytes;
    qint64 bytesReceived;
    qint64 fileNameSize;
    QString fileName;
    QFile *localFile;
    QByteArray inBlock;
};

#endif // WIDGET_H
