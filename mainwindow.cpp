#include "mainwindow.h"
#include "qtsession.h"
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>


MainWindow::MainWindow(QtSession* session) : session_(session)
{
  QWidget* centralWidget = new QWidget;
  searchEdit_ = new QLineEdit;
  connect(searchEdit_, SIGNAL(returnPressed()), SLOT(searchClick()));
  vLayout_ = new QVBoxLayout;
  vLayout_->addWidget(searchEdit_);
  centralWidget->setLayout(vLayout_);
  setCentralWidget(centralWidget);
}

void MainWindow::searchClick()
{
  qDebug() << "Search!";
}


