#pragma once

 #include <QAbstractListModel>
 #include <QList>

class Collection;
class CollectionItem;

 class CollectionModel : public QAbstractListModel
 {
     Q_OBJECT

 public:
		explicit CollectionModel(CollectionItem* prototype, QObject *parent);
		~CollectionModel();

		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role) const;

		void appendRow(CollectionItem *item);
		void appendRows(const QList<CollectionItem *> &items);
		void insertRow(int row, CollectionItem *item);

		//void handleItemChange();

		CollectionItem* find(const QString &hash) const;
		QModelIndex indexFromItem(const CollectionItem *item) const;

		void clear();

		bool removeRow(int row, const QModelIndex &parent);
		bool removeRows(int row, int count, const QModelIndex &parent);
		CollectionItem* takeRow(int row);

 private:
     QList<CollectionItem*> m_Collection;
 };

