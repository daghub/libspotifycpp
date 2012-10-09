#include "playlist.h"
#include "track.h"
#include "playlistmodel.h"

PlaylistModel::PlaylistModel(spotify::playlist_ptr pl, QObject* parent)
    : QAbstractListModel(parent), pl_(pl) {
  tracks_ = pl_->tracks();
  pl_state_changed_connnection_ = pl_->state_changed.connect(
      boost::bind(&PlaylistModel::onStateChanged, this));
  loaded_ = pl_->is_loaded();
}

void PlaylistModel::onStateChanged() {
  if (loaded_ != pl_->is_loaded()) {
    loaded_ = !loaded_;
    beginResetModel();
    tracks_ = pl_->tracks();
    endResetModel();
  }
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
  return tracks_.size();
}


QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() )
    return QVariant();

  if (index.row() >= (int) tracks_.size())
    return QVariant();

  if (role == Qt::DisplayRole) {
    return QString::fromUtf8(tracks_[index.row()]->name());
  }
  else
    return QVariant();
}

// TODO
QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation,
                                            int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return QAbstractItemModel::flags(index);
}


bool PlaylistModel::setData(const QModelIndex &index,
                                     const QVariant &value, int role) {
  if (index.isValid() && role == Qt::EditRole) {
    //stringList.replace(index.row(), value.toString());
    emit dataChanged(index, index);
    return true;
  }

  return false;
}

