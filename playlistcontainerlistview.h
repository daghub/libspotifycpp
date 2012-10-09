#ifndef PLAYLISTCONTAINERLISTVIEW_H
#define PLAYLISTCONTAINERLISTVIEW_H

#include <QListView>
#include "base.h"

class PlaylistcontainerListView : public QListView
{
  Q_OBJECT;
public:
  PlaylistcontainerListView(spotify::playlistcontainer_ptr pc);

public slots:
  void selectionChanged (const QItemSelection& selected, const QItemSelection& deselected);
private:
  spotify::playlistcontainer_ptr pc_;
};

#endif
