#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("new windows");
    dlg = new QDialog(this);

    /*QAction *openAction = new QAction(tr("&Open"), this);
    QIcon icon(":/images/li.jpg");
    openAction->setIcon(icon);

    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    ui->menu_F->addAction(openAction);*/

    isUntitled = true;
    curFile = tr("UnnamedFile.txt");
    setWindowTitle(curFile);

    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn = new QPushButton(tr("Search Next"), findDlg);
    QVBoxLayout *layout = new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    //connect(btn, SIGNAL(clicked(bool), this, SLOT(showFindText())));
    connect(btn, SIGNAL(clicked()),this,SLOT(showFindText()));

    //ui->statusBar->showMessage("Welcome to JieTrancender", 8000);  //显示8s钟
    statusLabel = new QLabel;
    statusLabel->setMinimumSize(150, 20);  //设置label大小
    statusLabel->setFrameShape(QFrame::WinPanel);  //设置标签形状
    statusLabel->setFrameShadow(QFrame::Sunken);  //设置标签阴影
    ui->statusBar->addWidget(statusLabel);
    statusLabel->setText("Welcome to jie-email@jie-trancender.org");

    QLabel *permanent = new QLabel(this);
    permanent->setFrameStyle(QFrame::Box | QFrame::Sunken);
    permanent->setText(tr("<a href = \"http://jie-trancender.org\">JTrancender</a>"));
    permanent->setTextFormat(Qt::RichText);
    permanent->setOpenExternalLinks(true);
    ui->statusBar->addPermanentWidget(permanent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//判断文档是否需要保存，如果已经保存完了，则新建文档，并初始化
void MainWindow::newFile()
{
    if (maybeSave())
    {
        isUntitled = true;
        curFile = tr("UnnamedFile.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

//判断文档是否需要保存
bool MainWindow::maybeSave()
{
    if (ui->textEdit->document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle("Warning");
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + " hasn't saved, is save?");
        QPushButton *yesBtn = box.addButton("Yes(&Y)", QMessageBox::YesRole);
        //QPushButton *noBtn = box.addButton("No(&N)", QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton("Cancel", QMessageBox::RejectRole);
        box.exec();

        if (box.clickedButton() == yesBtn)
        {
            return save();
        }
        else if (box.clickedButton() == cancelBtn)
        {
            return false;
        }
    }
    return true;
}

bool MainWindow::save()
{
    if (isUntitled)
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As", curFile);

    if (fileName.isEmpty())
    {
        return false;
    }
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Multi file editor", tr("can't write file %1:\n %2").arg(fileName).arg(file.errorString()));

        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);  //鼠标指针变为等待状态
    out << ui->textEdit->toPlainText();

    QApplication::restoreOverrideCursor();  //鼠标指针恢复原来的状态
    isUntitled = false;

    curFile = QFileInfo(fileName).canonicalFilePath();  //获得文件标准路径
    setWindowTitle(curFile);
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("多文档编辑器"), tr("无法读取文件 %1:\n%2").arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui->textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    curFile = QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::on_pushButton_clicked()
{
    //dlg = new QDialog(this);
    dlg->show();
}

void MainWindow::on_actionNew_N_triggered()
{
    newFile();
}

void MainWindow::on_actionBaocun_triggered()
{
    save();
}

void MainWindow::on_actionLin_triggered()
{
    saveAs();
}

void MainWindow::on_action_open_file_triggered()
{
    if (maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this);

        if (!fileName.isEmpty())
        {
            loadFile(fileName);
            ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_action_close_file_triggered()
{
    if (maybeSave())
    {
        ui->textEdit->setVisible(false);
    }
}

void MainWindow::on_action_exit_triggered()
{
    on_action_close_file_triggered();
    qApp->quit();
}

void MainWindow::on_action_revoke_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_action_cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_action_copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_action_paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::showFindText()
{
    QString str = findLineEdit->text();
    if (!ui->textEdit->find(str, QTextDocument::FindBackward))
    {
        QMessageBox::warning(this, tr("查找"), tr("找不到%1").arg(str));
    }
}

void MainWindow::on_actionFind_triggered()
{
    findDlg->show();
}
