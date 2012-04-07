#include "Collection.hpp"
#include "CollectionModel.hpp"
#include "CollectionItem.hpp"

#include <QSettings>

CollectionModel::CollectionModel(CollectionItem* prototype, QObject *parent) :
QAbstractListModel(parent)
{
	setRoleNames(prototype->roleNames());

	m_Collection = new Collection();
}

CollectionModel::~CollectionModel()
{
	clear();

	delete m_Collection;
}

void CollectionModel::Update()
{
	m_Collection->Update();

	clear();

	m_Collection->List([this](QString name, QString path, QString hash, qint64 size){
		this->appendRow(new CollectionItem(name, path, hash, size));
	});
}

int CollectionModel::rowCount(const QModelIndex &parent) const
{
	return m_List.size();
}

QVariant CollectionModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= m_List.size())
		return QVariant();

	return m_List.at(index.row())->data(role);
}

void CollectionModel::appendRow(CollectionItem *item)
{
	appendRows(QList<CollectionItem*>() << item);
}

void CollectionModel::appendRows(const QList<CollectionItem *> &items)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);
		foreach (CollectionItem *item, items)
		{
			//connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
			m_List.append(item);
		}
	endInsertRows();
}

void CollectionModel::insertRow(int row, CollectionItem *item)
{
	beginInsertRows(QModelIndex(), row, row);
		//connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
		m_List.insert(row, item);
	endInsertRows();
}

/*void CollectionModel::handleItemChange()
{
	CollectionItem* item = static_cast<CollectionItem*>(sender());

	QModelIndex index = indexFromItem(item);

	if (index.isValid())
		emit dataChanged(index, index);
}*/

CollectionItem * CollectionModel::find(const QString &hash) const
{
	foreach (CollectionItem* item, m_List)
	{
		if (item->hash() == hash)
			return item;
	}

	return 0;
}

QModelIndex CollectionModel::indexFromItem(const CollectionItem *item) const
{
	Q_ASSERT(item);

	for (int row = 0; row < m_List.size(); ++row)
	{
		if (m_List.at(row) == item)
			return index(row);
	}

	return QModelIndex();
}

void CollectionModel::clear()
{
	qDeleteAll(m_List);
	m_List.clear();

	reset();
}

bool CollectionModel::removeRow(int row, const QModelIndex &parent)
{
	Q_UNUSED(parent);

	if (row < 0 || row >= m_List.size())
		return false;

	beginRemoveRows(QModelIndex(), row, row);
		delete m_List.takeAt(row);
	endRemoveRows();

	return true;
}

bool CollectionModel::removeRows(int row, int count, const QModelIndex &parent)
{
	Q_UNUSED(parent);

	if (row < 0 || (row + count) >= m_List.size())
		return false;

	beginRemoveRows(QModelIndex(), row, row + count - 1);
		for(int i=0; i<count; ++i)
		{
			delete m_List.takeAt(row);
		}
	endRemoveRows();

	return true;
}

CollectionItem* CollectionModel::takeRow(int row)
{
	beginRemoveRows(QModelIndex(), row, row);
		CollectionItem* item = m_List.takeAt(row);
	endRemoveRows();

	return item;
}
