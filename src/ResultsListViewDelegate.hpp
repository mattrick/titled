#pragma once

#include <QStyledItemDelegate>

class ResultsListViewDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	public:
		ResultsListViewDelegate();
		virtual ~ResultsListViewDelegate();

		enum datarole {headerTextRole = Qt::UserRole + 100};

		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};
