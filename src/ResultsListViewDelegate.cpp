#include "ResultsListViewDelegate.hpp"

#include "ResultsItem.hpp"

#include <QFont>
#include <QApplication>
#include <QPainter>

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

    return(QSize(0 , fm.height() + 50));
}

void ResultsListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
	painter->save();

	if (option.state & QStyle::State_Selected)
	             painter->fillRect(option.rect, option.palette.highlight());



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

    QFont font = QApplication::font();
        //font.setPixelSize(font.weight()+);
        QFontMetrics fm(font);

        QString headerText = qvariant_cast<QString>(index.data(ResultsItem::TitleRole));

        qDebug() << headerText;

        QRect headerRect = option.rect;

        headerRect.setLeft(0);
        headerRect.setTop(headerRect.top()+5);
        headerRect.setBottom(headerRect.top()+fm.height());

        //painter->drawPixmap(QPoint(iconRect.right()/2,iconRect.top()/2),icon.pixmap(iconsize.width(),iconsize.height()));

        painter->setFont(font);
        painter->drawText(headerRect,headerText);

    painter->restore();

 }
