#pragma once

#include <QStyledItemDelegate>

class QListView;

class CollectionListViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	private:
		QListView* collectionListView;

	public:
		CollectionListViewDelegate(QListView* listview);
		virtual ~CollectionListViewDelegate();

		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		QSize trueSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};
