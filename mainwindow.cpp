#include <QDebug>
#include <QApplication>
#include <QTimer>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "mainwindow.h"
#include "qtsession.h"
#include "search.h"
#include "artist.h"

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
  search_ = session_->create_search(
      searchEdit_->text().toUtf8().data(),
      0, 80, 0, 80, 0, 80, 0, 80, SP_SEARCH_STANDARD);
  search_complete_connection_ = search_->complete.connect(
      boost::bind(&MainWindow::searchComplete, this));
}

void MainWindow::searchComplete()
{
  qDebug() << "completed!";
  std::vector< spotify::artist_ptr > artists(search_->artists());
  for (size_t i = 0; i < artists.size(); ++i) {
    qDebug() << "name: " << artists[i]->name();
  }
}
