#pragma once

#include <QStyledItemDelegate>

class QListView;

class ResultsListViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	private:
		QListView* resultsListView;

	public:
		ResultsListViewDelegate(QListView* listview);
		virtual ~ResultsListViewDelegate();

		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};
