#include "mainwindow.h"
#include "qtsession.h"
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>


MainWindow::MainWindow(QtSession* session) : session_(session)
{
  /*  try {
    logged_in_connection_ = session_->logged_in.connect(
        boost::bind(&MainWindow::loggedIn, this, _1));
  } catch(spotify::error& err) {
    qDebug() << boost::diagnostic_information(err).c_str();
    return;
    } */
  //  QWidget* centralWidget = new QWidget;
  //setCentralWidget(centralWidget);
}

