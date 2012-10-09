#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QWidget>
#include <QListView>
#include "base.h"

class QListView;
class QItemSelection;

class PlaylistWidget : public QWidget
{
  Q_OBJECT;
public:
  PlaylistWidget();
  void setPlaylist(spotify::playlist_ptr pl);

public slots:
  void selectionChanged (const QItemSelection& selected, const QItemSelection& deselected);
private:
  spotify::playlist_ptr playlist_;
  
  QListView* tracksView_;
};

#endif

