#include "Collection.hpp"
#include "CollectionModel.hpp"
#include "CollectionItem.hpp"

CollectionModel::CollectionModel(CollectionItem* prototype, QObject *parent) :
    QAbstractListModel(parent)
{
  setRoleNames(prototype->roleNames());
}

int CollectionModel::rowCount(const QModelIndex &parent) const
{
  return m_Collection.size();
}

QVariant CollectionModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() >= m_Collection.size())
    return QVariant();

  return m_Collection.at(index.row())->data(role);
}

CollectionModel::~CollectionModel() {
  clear();
}

void CollectionModel::appendRow(CollectionItem *item)
{
  appendRows(QList<CollectionItem*>() << item);
}

void CollectionModel::appendRows(const QList<CollectionItem *> &items)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
  foreach(CollectionItem *item, items) {
    //connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
    m_Collection.append(item);
  }
  endInsertRows();
}

void CollectionModel::insertRow(int row, CollectionItem *item)
{
  beginInsertRows(QModelIndex(), row, row);
  //connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
  m_Collection.insert(row, item);
  endInsertRows();
}

/*void CollectionModel::handleItemChange()
{
  ListItem* item = static_cast<ListItem*>(sender());
  QModelIndex index = indexFromItem(item);
  if(index.isValid())
    emit dataChanged(index, index);
}*/

CollectionItem * CollectionModel::find(const QString &hash) const
{
  foreach(CollectionItem* item, m_Collection) {
    if(item->hash() == hash) return item;
      }
  return 0;
}

QModelIndex CollectionModel::indexFromItem(const CollectionItem *item) const
{
  Q_ASSERT(item);
  for(int row=0; row<m_Collection.size(); ++row) {
    if(m_Collection.at(row) == item) return index(row);
  }
  return QModelIndex();
}

void CollectionModel::clear()
{
      qDeleteAll(m_Collection);
  m_Collection.clear();
}

bool CollectionModel::removeRow(int row, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  if(row < 0 || row >= m_Collection.size()) return false;
  beginRemoveRows(QModelIndex(), row, row);
  delete m_Collection.takeAt(row);
  endRemoveRows();
  return true;
}

bool CollectionModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  if(row < 0 || (row+count) >= m_Collection.size()) return false;
  beginRemoveRows(QModelIndex(), row, row+count-1);
  for(int i=0; i<count; ++i)
  {
    delete m_Collection.takeAt(row);
  }
  endRemoveRows();
  return true;
}

CollectionItem* CollectionModel::takeRow(int row)
{
  beginRemoveRows(QModelIndex(), row, row);
  CollectionItem* item = m_Collection.takeAt(row);
  endRemoveRows();
  return item;
}
