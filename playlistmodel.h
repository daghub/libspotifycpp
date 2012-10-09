#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include "base.h"

class PlaylistModel : public QAbstractListModel
{
  Q_OBJECT;

 public:
  PlaylistModel(spotify::playlist_ptr pl, QObject* parent = 0);

  virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
  virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  //bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  //bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

 private:
  void onStateChanged();

  spotify::playlist_ptr pl_;
  std::vector< spotify::track_ptr > tracks_;
  spotify::sig::scoped_connection pl_state_changed_connnection_;
  bool loaded_;
};

#endif
