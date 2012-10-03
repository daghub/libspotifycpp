#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <boost/scoped_ptr.hpp>
#include "session.h"

class QtSession;
class QLineEdit;
class QVBoxLayout;

class MainWindow : public QMainWindow
{
  Q_OBJECT;
public:
  MainWindow(QtSession* session);

public slots:
  void searchClick();

private:
  QtSession* session_;
  QLineEdit* searchEdit_;
  QVBoxLayout* vLayout_;
  //  spotify::sig::scoped_connection logged_in_connection_;

};

#endif
