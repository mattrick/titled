#include "CollectionItem.hpp"

CollectionItem::CollectionItem(QObject *parent)
{
}

CollectionItem::CollectionItem(const QString &name, const QString &path, const QString &hash, QObject *parent)
	: m_Name(name), m_Path(path), m_Hash(hash)
{
}

QHash<int, QByteArray> CollectionItem::roleNames() const
{
  QHash<int, QByteArray> names;
  names[NameRole] = "name";
  names[PathRole] = "path";
  names[HashRole] = "hash";
  return names;
}

QVariant CollectionItem::data(int role) const
{
  switch(role) {
  case Qt::DisplayRole:
    return name();
  case NameRole:
    return name();
  case PathRole:
    return path();
  case HashRole:
    return hash();
  default:
    return QVariant();
  }
}
