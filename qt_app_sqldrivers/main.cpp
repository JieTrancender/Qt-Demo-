#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //查看支持的数据库驱动
    qDebug() << "Available drivers:";
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers)
        qDebug() << driver;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mydata");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open())
    {
        return false;
    }

    QSqlQuery query;

    query.exec("create table student(id int primary key, name varchar(18))");

    query.exec("insert into student values(1, 'Jie Mo')");
    query.exec("insert into student values(2, 'Huo Zhiqiang')");
    query.exec("insert into student values(3, 'Zhang Xiquan')");

    query.exec("select id, name from student where id >= 2");

    while (query.next())
    {
        int value0 = query.value(0).toInt();
        QString value1 = query.value(1).toString();

        qDebug() << value0 << ' ' << value1;
    }


    return a.exec();
}
