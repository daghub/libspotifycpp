#ifndef PLAYLISTCONTAINERMODEL_H
#define PLAYLISTCONTAINERMODEL_H

#include <QAbstractListModel>
#include "base.h"

class PlaylistcontainerModel : public QAbstractListModel
{
  Q_OBJECT;

 public:
  PlaylistcontainerModel(spotify::playlistcontainer_ptr pc, QObject* parent = 0);

  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

 private:
  void onLoaded();

  spotify::playlistcontainer_ptr pc_;
  std::vector< spotify::playlist_ptr > playlists_;
  spotify::sig::scoped_connection pc_loaded_connnection_;
};

#endif
