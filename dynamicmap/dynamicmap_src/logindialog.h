#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    QString getUsername();
    QString getPassword();
    void resetForm();
    
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
