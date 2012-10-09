#include "playlistcontainer.h"
#include "playlist.h"
#include "playlistcontainermodel.h"

PlaylistcontainerModel::PlaylistcontainerModel(spotify::playlistcontainer_ptr pc, QObject* parent)
    : QAbstractListModel(parent), pc_(pc) {
  playlists_ = pc_->playlists();
  pc_loaded_connnection_ = pc_->loaded.connect(
      boost::bind(&PlaylistcontainerModel::onLoaded, this));
}

void PlaylistcontainerModel::onLoaded() {
  beginResetModel();
  playlists_ = pc_->playlists();
  endResetModel();
  emit dataChanged(index(0, 0), index(playlists_.size(), 0));
  //beginInsertRows(QModelIndex(), 0, playlists_.size());

  // for (int row = 0; row < rows; ++row) {
  //       stringList.insert(position, "");
  //   }

  //endInsertRows();
  //emit dataChanged(index(0, 0), index(playlists_.size(), 0));

  // insertRows(0, playlists_.size(), QModelIndex());
  // for (int row = 0; row < (int)playlists_.size(); ++row) {
  //   QModelIndex index = this->index(row, 0, QModelIndex());
  //   setData(index, playlists_[row]->name());
  // }
}

int PlaylistcontainerModel::rowCount(const QModelIndex &parent) const
{
  return playlists_.size();
}


QVariant PlaylistcontainerModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() )
    return QVariant();

  if (index.row() >= (int) playlists_.size())
    return QVariant();

  if (role == Qt::DisplayRole) {
    return QString::fromUtf8(playlists_[index.row()]->name());
  }
  else
    return QVariant();
}

// TODO
QVariant PlaylistcontainerModel::headerData(int section, Qt::Orientation orientation,
                                            int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
}


/*!
    Returns an appropriate value for the item's flags. Valid items are
    enabled, selectable, and editable.
*/
Qt::ItemFlags PlaylistcontainerModel::flags(const QModelIndex &index) const
{
    if (index.isValid())
      return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return QAbstractItemModel::flags(index);
}


bool PlaylistcontainerModel::setData(const QModelIndex &index,
                                     const QVariant &value, int role) {
  if (index.isValid() && role == Qt::EditRole) {
    //stringList.replace(index.row(), value.toString());
    emit dataChanged(index, index);
    return true;
  }

  return false;
}


/*!
    Inserts a number of rows into the model at the specified position.
*/


bool PlaylistcontainerModel::insertRows(int position, int rows, const QModelIndex &parent)
{
  /*    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.insert(position, "");
    }

    endInsertRows(); */
    return true;
 
}


/*!
    Removes a number of rows from the model at the specified position.
*/


bool PlaylistcontainerModel::removeRows(int position, int rows, const QModelIndex &parent)
{
  /*beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        stringList.removeAt(position);
    }

    endRemoveRows(); */
    return true;
 
}
