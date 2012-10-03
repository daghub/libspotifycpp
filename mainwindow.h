#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "base.h"


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
  void searchComplete();

private:
  QtSession* session_;
  QLineEdit* searchEdit_;
  QVBoxLayout* vLayout_;
  spotify::search_ptr search_;
  spotify::sig::scoped_connection search_complete_connection_;

};

#endif
