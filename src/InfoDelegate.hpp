#pragma once

#include <QStyledItemDelegate>

class QListView;

class InfoDelegate : public QStyledItemDelegate
{
	Q_OBJECT

	private:
		QListView* m_ListView;

	public:
		InfoDelegate(QListView* listview);
		virtual ~InfoDelegate();

		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};
