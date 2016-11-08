#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QCloseEvent>

class QLineEdit;
class QDialog;
class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &fileName);

private slots:
    void on_pushButton_clicked();

    void on_actionNew_N_triggered();

    void on_actionBaocun_triggered();

    void on_actionLin_triggered();

    void on_action_open_file_triggered();

    void on_action_close_file_triggered();

    void on_action_exit_triggered();

    void on_action_revoke_triggered();

    void on_action_cut_triggered();

    void on_action_copy_triggered();

    void on_action_paste_triggered();

    void showFindText();

    void on_actionFind_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QDialog *dlg;
    bool isUntitled;  //为真表明没有保存过，否则已经被保存了
    QString curFile;  //保存当前文件的路径
    QLineEdit *findLineEdit;
    QDialog *findDlg;
    QLabel *statusLabel;
};

#endif // MAINWINDOW_H
