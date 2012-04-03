#include "CollectionListViewDelegate.hpp"

#include <QFont>
#include <QApplication>
#include <QPainter>

CollectionListViewDelegate::CollectionListViewDelegate()
{
}

CollectionListViewDelegate::~CollectionListViewDelegate()
{
}

QSize CollectionListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QFont font = QApplication::font();
    QFontMetrics fm(font);

    return(QSize(0 , fm.height()));

}

void CollectionListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
    QStyledItemDelegate::paint(painter,option,index);
 }
