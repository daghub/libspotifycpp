#include "mainwindow.h"
#include "session.h"
#include <QDebug>
#include <QApplication>
#include <QTimer>

QtSession::QtSession()
{
  // Get started processing events
  processEvents();
}

QtSession::~QtSession()
{
}


void QtSession::notifyMainThread()
{
  //  qApp->wakeUpGuiThread(); // needed?
  QTimer::singleShot(0, this, SLOT(processEvents));
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
        boost::bind(&MainWindow::logged_in, this, _1));
    session_->login("<todo>", "<todo>", false, 0);
  } catch(spotify::error& err) {
    qDebug() << boost::diagnostic_information(err).c_str();
  }
}

void MainWindow::logged_in(sp_error err)
{
  qDebug() << "logged_in: " << err;
}

