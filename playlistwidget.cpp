#include <QVBoxLayout>
#include <QItemSelectionModel>
#include <QDebug>
#include "playlistwidget.h"
#include "session.h"
#include "playlistmodel.h"


PlaylistWidget::PlaylistWidget() {
  QVBoxLayout* layout = new QVBoxLayout;
  setLayout(layout);

  tracksView_ = new QListView;
  layout->addWidget(tracksView_);

  tracksView_->setSelectionBehavior(QAbstractItemView::SelectRows);
  tracksView_->setSelectionMode(QAbstractItemView::SingleSelection);
  QItemSelectionModel* selectionModel = tracksView_->selectionModel();
  connect(selectionModel,
          SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
          SLOT(selectionChanged(const QItemSelection &, const QItemSelection &)));
}

void PlaylistWidget::setPlaylist(spotify::playlist_ptr pl) {
  QAbstractItemModel *model = new PlaylistModel(pl);
  tracksView_->setModel(model);
}

void PlaylistWidget::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected) {
  qDebug() << "selectionChanged";
}

