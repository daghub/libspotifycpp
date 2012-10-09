#include <QItemSelectionModel>
#include <QDebug>
#include "playlistcontainermodel.h"
#include "playlistcontainerlistview.h"

PlaylistcontainerListView::PlaylistcontainerListView(spotify::playlistcontainer_ptr pc)
    : pc_(pc) {
  QAbstractItemModel *model = new PlaylistcontainerModel(pc_);
  setModel(model);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);

  QItemSelectionModel* selectionModel = this->selectionModel();
  connect(selectionModel,
          SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
          SLOT(selectionChanged(const QItemSelection &, const QItemSelection &)));
}

void PlaylistcontainerListView::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
  qDebug() << "selectionChanged";
}
