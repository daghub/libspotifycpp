#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QListView>
#include "base.h"

class QListView;
class QItemSelection;

class LibraryWidget : public QWidget
{
  Q_OBJECT;
public:
  LibraryWidget(spotify::session* session);
public slots:
  void selectionChanged (const QItemSelection& selected, const QItemSelection& deselected);
private:
  spotify::session* session_;
  QListView* playlistsListView_;
};

#endif

