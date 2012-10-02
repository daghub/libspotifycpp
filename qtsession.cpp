#include <QTimer>
#include <QDebug>
#include "qtsession.h"

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

