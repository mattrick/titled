#pragma once

#include <QStyledItemDelegate>

class CollectionListViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	public:
		CollectionListViewDelegate();
		virtual ~CollectionListViewDelegate();

		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};
