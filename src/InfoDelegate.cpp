#include <QFont>
#include <QApplication>
#include <QPainter>
#include <QTextOption>
#include <QListView>
#include <QScrollBar>

#include "InfoDelegate.hpp"
#include "InfoItem.hpp"

InfoDelegate::InfoDelegate(QListView* listview)
	: m_ListView(listview)
{
}

InfoDelegate::~InfoDelegate()
{
}

QSize InfoDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
    QFont font = QApplication::font();
    QFontMetrics fm(font);

    QString headerText = index.data(InfoItem::InfoHeaderRole).toString();
    QString subText = index.data(InfoItem::InfoSubRole).toString();

    QFont subFont(font);
    subFont.setPointSize(font.pointSize() - 2);

    QFontMetrics sfm(subFont);

    return QSize(std::max(fm.width(headerText), sfm.width(subText)), 5 + fm.height() + sfm.height() + 5);
}

#include <QDebug>

void InfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

	QString headerText = index.data(InfoItem::InfoHeaderRole).toString();

	QRect headerRect = option.rect;

	headerRect.setTop(headerRect.top()+5);
	headerRect.setBottom(headerRect.top()+fm.height());

	QString subText = index.data(InfoItem::InfoSubRole).toString();

	QRect subRect = option.rect;

	subRect.setTop(headerRect.bottom());
	subRect.setBottom(subRect.top() + sfm.height());

	painter->setFont(font);
	painter->drawText(headerRect,headerText, QTextOption(Qt::AlignHCenter));

	painter->setFont(subFont);
	painter->drawText(subRect,subText, QTextOption(Qt::AlignHCenter));


	painter->restore();

}
