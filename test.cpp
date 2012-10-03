#include <QApplication>
#include <QDialog>
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

  if (loginDialog.exec() == QDialog::Accepted) {
    MainWindow mainWindow(&session);
    mainWindow.show();
    return app.exec();
  }

  return 0;
}

