#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <boost/scoped_ptr.hpp>
#include "session.h"

class QtSession;

class MainWindow : public QMainWindow
{
  Q_OBJECT;
public:
  MainWindow(QtSession* session);

private:
  QtSession* session_;
  //  spotify::sig::scoped_connection logged_in_connection_;

};

#endif
