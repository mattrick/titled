#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QStringList>

class ResultsItem;

class ResultsModel : public QAbstractListModel
{
	Q_OBJECT

	private:
		QList<ResultsItem*> m_List;

	/* QAbstractListModel */
		void appendRow(ResultsItem *item);
		void appendRows(const QList<ResultsItem *> &items);
		void insertRow(int row, ResultsItem *item);

		//void handleItemChange();

		ResultsItem* find(const QString &hash) const;
		QModelIndex indexFromItem(const ResultsItem *item) const;

		void clear();

		bool removeRow(int row, const QModelIndex &parent);
		bool removeRows(int row, int count, const QModelIndex &parent);
		ResultsItem* takeRow(int row);

		void UpdateList();

	protected:

	public:
		explicit ResultsModel(ResultsItem* prototype, QObject *parent);
		~ResultsModel();

		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant data(const QModelIndex &index, int role) const;

	public slots:
		void Update();
};

