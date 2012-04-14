#pragma once

#include <QStyledItemDelegate>

class QListView;

class CollectionListViewDelegate : public QStyledItemDelegate
{
	private:
		QListView* collectionListView;

	public:
		CollectionListViewDelegate(QListView* listview);
		~CollectionListViewDelegate();

		void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
		QSize trueSizeHint(const QStyleOptionViewItem& option, const QModelIndex& index ) const;
		QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index ) const;
};
