#include "MyListModel.hpp"

MyListModel::MyListModel(QObject *parent)
	: QAbstractListModel(parent)
{
}

MyListModel::~MyListModel()
{
	clear();
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
	return m_List.size();
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= m_List.size())
		return QVariant();

	return m_List.at(index.row())->data(role);
}

void MyListModel::appendRow(QStandardItem *item)
{
	appendRows(QList<QStandardItem*>() << item);
}

void MyListModel::appendRows(const QList<QStandardItem *> &items)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);
		foreach (QStandardItem *item, items)
		{
			//connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
			m_List.append(item);
		}
	endInsertRows();
}

void MyListModel::insertRow(int row, QStandardItem *item)
{
	beginInsertRows(QModelIndex(), row, row);
		//connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
		m_List.insert(row, item);
	endInsertRows();
}

//void MyListModel::handleItemChange();

/*T* MyListModel::find(const QString &hash) const
{
	foreach (CollectionItem* item, m_List)
	{
		if (item->hash() == hash)
			return item;
	}

	return 0;
}*/

QModelIndex MyListModel::indexFromItem(const QStandardItem *item) const
{
	Q_ASSERT(item);

	for (int row = 0; row < m_List.size(); ++row)
	{
		if (m_List.at(row) == item)
			return index(row);
	}

	return QModelIndex();
}

void MyListModel::clear()
{
	qDeleteAll(m_List);
	m_List.clear();

	reset();
}

bool MyListModel::removeRow(int row, const QModelIndex &parent)
{
	Q_UNUSED(parent);

	if (row < 0 || row >= m_List.size())
		return false;

	beginRemoveRows(QModelIndex(), row, row);
		delete m_List.takeAt(row);
	endRemoveRows();

	return true;
}

bool MyListModel::removeRows(int row, int count, const QModelIndex &parent)
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

QStandardItem* MyListModel::takeRow(int row)
{
	beginRemoveRows(QModelIndex(), row, row);
		QStandardItem* item = m_List.takeAt(row);
	endRemoveRows();

	return item;
}

Qt::ItemFlags MyListModel::flags(const QModelIndex &index) const
{
	return m_List.at(index.row())->flags();
}
