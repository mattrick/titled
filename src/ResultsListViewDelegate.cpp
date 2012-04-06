#include "ResultsListViewDelegate.hpp"

#include <QFont>
#include <QApplication>
#include <QPainter>
#include <QTextOption>

#include "ResultsItem.hpp"

#include <QListView>
#include <QScrollBar>
#include <QDebug>

ResultsListViewDelegate::ResultsListViewDelegate(QListView* listview)
	: resultsListView(listview)
{
}

ResultsListViewDelegate::~ResultsListViewDelegate()
{
}

QSize ResultsListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QFont font = QApplication::font();

    QFontMetrics fm(font);
    QString headerText = index.data(ResultsItem::TitleRole).toString();
    if (!index.data(ResultsItem::YearRole).toString().isEmpty())
    	headerText += " (" + index.data(ResultsItem::YearRole).toString() + ")";

    QFont subFont(font);
    subFont.setPointSize(font.pointSize() - 2);

    QFontMetrics sfm(subFont);
    QString subText = index.data(ResultsItem::OriginalRole).toString();

    QSize hint;

    hint.setWidth(std::max(fm.width(headerText), sfm.width(subText)));

    hint.setHeight(5 + fm.height() + sfm.height() + 5);

    return(hint);
}

void ResultsListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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


	QString headerText = index.data(ResultsItem::TitleRole).toString();
	if (!index.data(ResultsItem::YearRole).toString().isEmpty())
		headerText += " (" + index.data(ResultsItem::YearRole).toString() + ")";

	QString subText = index.data(ResultsItem::OriginalRole).toString();


	QSize size(sizeHint(option, index));

	QTextOption textOption(Qt::AlignHCenter);

	QRect basicRect = option.rect;

	if (option.rect.width() > resultsListView->width())
	{
		if (size.width() <= resultsListView->width())
		{
			basicRect.setLeft(0);
			basicRect.setRight(resultsListView->width());
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
