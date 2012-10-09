#include <QVBoxLayout>
#include <QStringListModel>
#include <QItemSelectionModel>
#include <QDebug>
#include "librarywidget.h"
#include "session.h"
#include "playlistcontainermodel.h"
#include "playlistcontainerlistview.h"


LibraryWidget::LibraryWidget(spotify::session* session) : session_(session) {
  QVBoxLayout* layout = new QVBoxLayout;
  setLayout(layout);

  playlistsListView_ = new PlaylistcontainerListView(session_->playlistcontainer());
  layout->addWidget(playlistsListView_);

}

void LibraryWidget::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
  qDebug() << "selectionChanged";
}

