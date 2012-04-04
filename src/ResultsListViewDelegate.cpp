#include "ResultsListViewDelegate.hpp"

#include "ResultsItem.hpp"

#include <QFont>
#include <QApplication>
#include <QPainter>
#include <QTextOption>

#include <QDebug>

ResultsListViewDelegate::ResultsListViewDelegate()
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
	             painter->fillRect(option.rect, option.palette.highlight());

	/*
	 * TODO:
	 *
	 * Fix graphical bug which occures when text is horizontally centered and longer than view's rect.
	 *
	 */

	/*QBrush backBrush;
	    QColor foreColor;
	    bool hover = false;
	    if ( option.state & QStyle::State_MouseOver )
	    {
	           backBrush = option.palette.color( QPalette::Highlight ).light( 115 );
	           foreColor = option.palette.color( QPalette::HighlightedText );
	           hover = true;
	    }
	    QStyleOptionViewItemV4 optionV4(option);
	    initStyleOption(&optionV4, index);*/

    /*const QStyle *style = optionV4.widget ? optionV4.widget->style() : QApplication::style();
       const QWidget* widget = optionV4.widget;
       if( hover )
       {
               optionV4.backgroundBrush = backBrush;
       }
       painter->save();
       style->drawPrimitive(QStyle::PE_PanelItemViewItem, &option, painter, widget);
       painter->restore();
       switch( index.column() )
       {
       case 0: // we want default behavior
           style->drawControl(QStyle::CE_ItemViewItem, &option, painter, widget);
           break;
       case 1:
       // some custom drawText
       break;
       case 2:
       // draw a QStyleOptionProgressBar
       break;
       }*/

	if (option.state & QStyle::State_Selected)
		painter->setPen(option.palette.highlightedText().color());

		QFont font = QApplication::font();
        QFontMetrics fm(font);

        QString headerText = index.data(ResultsItem::TitleRole).toString();
        if (!index.data(ResultsItem::YearRole).toString().isEmpty())
            	headerText += " (" + index.data(ResultsItem::YearRole).toString() + ")";

        QRect headerRect = option.rect;

        headerRect.setLeft(0);
        headerRect.setTop(headerRect.top()+5);
        headerRect.setBottom(headerRect.top()+fm.height());

        //painter->drawPixmap(QPoint(iconRect.right()/2,iconRect.top()/2),icon.pixmap(iconsize.width(),iconsize.height()));


        painter->setFont(font);
        painter->drawText(headerRect,headerText, QTextOption(Qt::AlignHCenter));

 QFont subFont(font);
           subFont.setPointSize(font.pointSize() - 2);

           QFontMetrics sfm(subFont);
           QString subText = index.data(ResultsItem::OriginalRole).toString();

        QRect subRect = option.rect;

        subRect.setLeft(0);
        subRect.setTop(headerRect.bottom());
        subRect.setBottom(subRect.top() + sfm.height());

        painter->setFont(subFont);
                painter->drawText(subRect,subText, QTextOption(Qt::AlignHCenter));

    painter->restore();

 }
