#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->userLineEdit->setFocus();
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    ui->pwdLineEdit->setPlaceholderText("input password");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    accept();
    if (ui->userLineEdit->text().trimmed() == tr("1467159125") && ui->pwdLineEdit->text() == tr("123456"))
    {
        accept();
    }
    else
    {
        //QMessageBox::warning(this, tr("Warning"), tr("User name or password error"), QMessageBox::Yes);

        ui->userLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->userLineEdit->setFocus();
    }
}
