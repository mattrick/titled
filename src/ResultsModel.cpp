#include "ResultsModel.hpp"
#include "ResultsItem.hpp"

#include <QSettings>


ResultsModel::ResultsModel(ResultsItem* prototype, QObject *parent) :
QAbstractListModel(parent)
{
	setRoleNames(prototype->roleNames());
}

int ResultsModel::rowCount(const QModelIndex &parent) const
{
	return m_List.size();
}

QVariant ResultsModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= m_List.size())
		return QVariant();

	return m_List.at(index.row())->data(role);
}

ResultsModel::~ResultsModel()
{
	clear();
}

void ResultsModel::appendRow(ResultsItem *item)
{
	appendRows(QList<ResultsItem*>() << item);
}

void ResultsModel::appendRows(const QList<ResultsItem *> &items)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount() + items.size() - 1);
		foreach (ResultsItem *item, items)
		{
			//connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
			m_List.append(item);
		}
	endInsertRows();
}

void ResultsModel::insertRow(int row, ResultsItem *item)
{
	beginInsertRows(QModelIndex(), row, row);
		//connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
		m_List.insert(row, item);
	endInsertRows();
}

/*void ResultsModel::handleItemChange()
{
	ResultsItem* item = static_cast<ResultsItem*>(sender());

	QModelIndex index = indexFromItem(item);

	if (index.isValid())
		emit dataChanged(index, index);
}*/

/*ResultsItem * ResultsModel::find(const QString &hash) const
{
	foreach (ResultsItem* item, m_List)
	{
		if (item->hash() == hash)
			return item;
	}

	return 0;
}*/

QModelIndex ResultsModel::indexFromItem(const ResultsItem *item) const
{
	Q_ASSERT(item);

	for (int row = 0; row < m_List.size(); ++row)
	{
		if (m_List.at(row) == item)
			return index(row);
	}

	return QModelIndex();
}

void ResultsModel::clear()
{
	qDeleteAll(m_List);
	m_List.clear();
}

bool ResultsModel::removeRow(int row, const QModelIndex &parent)
{
	Q_UNUSED(parent);

	if (row < 0 || row >= m_List.size())
		return false;

	beginRemoveRows(QModelIndex(), row, row);
		delete m_List.takeAt(row);
	endRemoveRows();

	return true;
}

bool ResultsModel::removeRows(int row, int count, const QModelIndex &parent)
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

ResultsItem* ResultsModel::takeRow(int row)
{
	beginRemoveRows(QModelIndex(), row, row);
		ResultsItem* item = m_List.takeAt(row);
	endRemoveRows();

	return item;
}

void ResultsModel::printError()
{
	clear();

	appendRow(new ResultsItem(tr("Error fetching search results: timeout"), "", "", ""));
}

void ResultsModel::printEmpty()
{
	clear();

	appendRow(new ResultsItem(tr("No matching titles, change your query"), "", "", ""));
}
