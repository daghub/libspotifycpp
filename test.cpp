#include <QApplication>
#include "mainwindow.h"
#include "logindialog.h"
#include "qtsession.h"


int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  QtSession session;
  app.setOrganizationName("Spotify");
  app.setApplicationName("libspotify sample");
  LoginDialog loginDialog(&session);
  int ret = loginDialog.exec();
  //  MainWindow mainWindow;
  //mainWindow.show();
  return app.exec();
}

