#include "mainwindow.h"
#include "session.h"
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

QtSession::QtSession()
{
  // Get started processing events
  processEvents();
}

QtSession::~QtSession()
{
}


void QtSession::notify_main_thread()
{
  //  qApp->wakeUpGuiThread(); // needed?
  QTimer::singleShot(0, this, SLOT(processEvents()));
}

void QtSession::log_message(const char* data) const
{
  fprintf(stderr, "%s", data);
}

void QtSession::processEvents()
{
  int next_timeout;
  try {
    while (!(next_timeout = process_events()))
      ;
    QTimer::singleShot(std::min(next_timeout, 500), this, SLOT(processEvents()));
  } catch (spotify::error& err) {
    qDebug() << boost::diagnostic_information(err).c_str();
  }
}

MainWindow::MainWindow()
{
  try {
    session_.reset(new QtSession);
    logged_in_connection_ = session_->logged_in.connect(
        boost::bind(&MainWindow::loggedIn, this, _1));
  } catch(spotify::error& err) {
    qDebug() << boost::diagnostic_information(err).c_str();
    return;
  }
  QWidget* centralWidget = new QWidget;
  userName_ = new QLineEdit;
  password_ = new QLineEdit;
  userName_->setText("User name");
  password_->setEchoMode(QLineEdit::Password);
  login_ = new QPushButton;
  login_->setText("Login");
  connect(login_, SIGNAL(clicked()), this, SLOT(loginClick()));
  QHBoxLayout* layout = new QHBoxLayout;
  layout->addWidget(userName_);
  layout->addWidget(password_);
  layout->addWidget(login_);
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
}

void MainWindow::loginClick()
{
  try {
    session_->login(userName_->text().toUtf8().data(),
                    password_->text().toUtf8().data(),
                    false, 0);
    login_->setEnabled(false);
  } catch(spotify::error& err) {
    qDebug() << boost::diagnostic_information(err).c_str();
    return;
  }
}

void MainWindow::loggedIn(sp_error err)
{
  qDebug() << "logged_in: " << err;
  if (err == SP_ERROR_OK) {
    login_->setText("Logout");
  }
  login_->setEnabled(true);
}

