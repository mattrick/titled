#include "CollectionListViewDelegate.hpp"

#include <QFont>
#include <QApplication>
#include <QPainter>
#include <QTextOption>

#include "CollectionItem.hpp"

#include <QListView>
#include <QScrollBar>

CollectionListViewDelegate::CollectionListViewDelegate(QListView* listview)
	: collectionListView(listview)
{
}

CollectionListViewDelegate::~CollectionListViewDelegate()
{
}

QSize CollectionListViewDelegate::trueSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QFont font = QApplication::font();
    QFontMetrics fm(font);

    QString headerText = index.data(CollectionItem::NameRole).toString();

    QFont subFont(font);
    subFont.setPointSize(font.pointSize() - 2);

    QFontMetrics sfm(subFont);
    QString subText = 	index.data(CollectionItem::SizeTextRole).toString() + " | " + \
    					"subdir: " + index.data(CollectionItem::SubdirTextRole).toString();

    QSize hint;

    hint.setWidth(std::max(fm.width(headerText), sfm.width(subText)));

    hint.setHeight(5 + fm.height() + sfm.height() + 5);

    return(hint);
}

QSize CollectionListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QSize hint = trueSizeHint(option, index);

	// we don't want item to be bigger than listView
	int scrollBarWidth = 0;

	if (collectionListView->verticalScrollBar())
		scrollBarWidth = collectionListView->verticalScrollBar()->width();

	hint.setWidth(std::min(hint.width(), collectionListView->viewport()->width() - scrollBarWidth));

	return hint;
}

void CollectionListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	painter->save();


	if (option.state & QStyle::State_Selected)
	{
		painter->fillRect(option.rect, option.palette.highlight());
		painter->setPen(option.palette.highlightedText().color());
	}


	QFont font = QApplication::font();
	QFontMetrics fm(font);

	QFont subFont(font);
	subFont.setPointSize(font.pointSize() - 2);

	QFontMetrics sfm(subFont);


	QString headerText = index.data(CollectionItem::NameRole).toString();

	QString subText = 	index.data(CollectionItem::SizeTextRole).toString() + " | " + \
						"subdir: " + index.data(CollectionItem::SubdirTextRole).toString();

	QSize trueSize(trueSizeHint(option, index));
	QSize size(sizeHint(option, index));

	if (trueSize.width() != size.width())
	{
		int n = 0;

		if (fm.width(headerText) > size.width())
		{
			for (n = headerText.size(); fm.width(QString(headerText.left(n) + "...")) > option.rect.width(); n--);
			headerText = headerText.left(n) + "...";
		}
	}

	QTextOption textOption(Qt::AlignHCenter);

	QRect basicRect = option.rect;

	if (option.rect.width() > collectionListView->width())
	{
		if (size.width() <= collectionListView->width())
		{
			basicRect.setLeft(0);
			basicRect.setRight(collectionListView->width());
		}
	}

	QRect headerRect = basicRect;

	headerRect.setTop(headerRect.top()+5);
	headerRect.setBottom(headerRect.top()+fm.height());

	QRect subRect = basicRect;

	subRect.setTop(headerRect.bottom());
	subRect.setBottom(subRect.top() + sfm.height());


	painter->setFont(font);
	painter->drawText(headerRect,headerText, textOption);


	painter->setFont(subFont);
	painter->drawText(subRect,subText, textOption);

	painter->restore();

}
