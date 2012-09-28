#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <boost/scoped_ptr.hpp>
#include "session.h"

class QPushButton;
class QLineEdit;

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
public slots:
  void loginClick();

private:
  void loggedIn(sp_error err);
  spotify::sig::scoped_connection logged_in_connection_;
  boost::scoped_ptr< QtSession > session_;

  QLineEdit* userName_;
  QLineEdit* password_;
  QPushButton* login_;
};

#endif
