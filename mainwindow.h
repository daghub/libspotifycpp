#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <boost/scoped_ptr.hpp>
#include "session.h"

class QtSession : public QObject , public spotify::session
{
  Q_OBJECT;
public:
  QtSession();
  virtual ~QtSession();

  public slots:
  void processEvents();

private:
  // Overrides
  virtual void notify_main_thread();
  virtual void log_message(const char* data) const;

};

class MainWindow : public QMainWindow
{
  Q_OBJECT;
public:
  MainWindow();
private:
  void logged_in(sp_error err);
  spotify::sig::scoped_connection logged_in_connection_;
  boost::scoped_ptr< QtSession > session_;
};

#endif
