#pragma once

#include <QAbstractListModel>
#include <QStandardItem>
#include <QList>

class MyListModel : public QAbstractListModel
{
	private:
		QList<QStandardItem*> m_List;

	protected:

	public:
		MyListModel(QObject *parent = 0);
		~MyListModel();

		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		QVariant data(const QModelIndex &index, int role) const;

		void appendRow(QStandardItem *item);
		void appendRows(const QList<QStandardItem *> &items);
		void insertRow(int row, QStandardItem *item);

		//void handleItemChange();

		//T* find(const QString &hash) const;

		QModelIndex indexFromItem(const QStandardItem *item) const;

		void clear();

		bool removeRow(int row, const QModelIndex &parent);
		bool removeRows(int row, int count, const QModelIndex &parent);
		QStandardItem* takeRow(int row);

		Qt::ItemFlags flags(const QModelIndex &index) const;
};
