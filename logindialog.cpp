#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include "qtsession.h"
#include "logindialog.h"

LoginDialog::LoginDialog(QtSession* session) : session_(session)
{
  QLabel* logo = new QLabel;
  logo->setPixmap(QPixmap("logo.png"));
  QLabel* text1 = new QLabel("Username");
  QLabel* text2 = new QLabel("Password");
  userName_ = new QLineEdit;
  password_ = new QLineEdit;
  userName_->setText("User name");
  password_->setEchoMode(QLineEdit::Password);
  login_ = new QPushButton;
  login_->setText("Login");
  connect(login_, SIGNAL(clicked()), this, SLOT(loginClick()));
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(logo);
  layout->addWidget(text1);
  layout->addWidget(userName_);
  layout->addWidget(text2);
  layout->addWidget(password_);
  layout->addWidget(login_);

  setLayout(layout);
  layout->setSizeConstraint(QLayout::SetFixedSize);
}

void LoginDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.drawImage(0, 0, QImage("background.png"));
}

void LoginDialog::loginClick()
{
  try {
    session_->login(userName_->text().toUtf8().data(),
                    password_->text().toUtf8().data(),
                    false, 0);
    login_->setEnabled(false);
    logged_in_connection_ = session_->logged_in.connect(
        boost::bind(&LoginDialog::loggedIn, this, _1));
  } catch(spotify::error& err) {
    qDebug() << boost::diagnostic_information(err).c_str();
    return;
  }
}

void LoginDialog::loggedIn(sp_error err)
{
  qDebug() << "logged_in: " << err;
  if (err == SP_ERROR_OK) {
    done(QDialog::Accepted);
  };
  login_->setEnabled(true);
}


