#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QNetworkReply>
#include <QFileInfo>
#include <QNetworkInterface>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startRequest(QUrl url);
private slots:
    void on_pushButton_clicked();  //下载按钮的单击事件槽
    void httpFinished();  //完成下载后的处理
    void httpReadyRead();  //接收到数据时的处理
    void updateDataReadProgress(qint64, qint64);  //更新进度条

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;  //用来发送请求和接收请求
    QNetworkReply *reply;
    QUrl url;
    QFile *file;
};

#endif // MAINWINDOW_H
