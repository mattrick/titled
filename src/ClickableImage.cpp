#include "ClickableImage.hpp"

#include <QPixmap>
#include <QMouseEvent>

ClickableImage::ClickableImage(QPoint pos, QPixmap image, QWidget* parent)
	: QLabel(parent), m_Clicked(false)
{
	setPixmap(image);
	setGeometry(QRect(pos.x(), pos.y(), image.width(), image.height()));
}

ClickableImage::~ClickableImage()
{

}

void ClickableImage::mousePressEvent ( QMouseEvent * e )
{
	m_Point = e->pos();
	m_Clicked = true;
}

void ClickableImage::mouseReleaseEvent ( QMouseEvent * e )
{

	    if ((m_Clicked) && (e->pos() == m_Point))
	        emit clicked();
}


