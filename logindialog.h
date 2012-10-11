#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "session.h"

class QPushButton;
class QLineEdit;
class QCheckBox;
class QtSession;

class LoginDialog : public QDialog
{
  Q_OBJECT;
public:
  LoginDialog(QtSession* session);

public slots:
  void loginClick();

protected:
  void paintEvent(QPaintEvent *event);

private:
  void loggedIn(sp_error err);

  spotify::sig::scoped_connection logged_in_connection_;
  QtSession* session_;

  QLineEdit* userName_;
  QLineEdit* password_;
  QPushButton* login_;
  QCheckBox* rememberMe_;
};

#endif

