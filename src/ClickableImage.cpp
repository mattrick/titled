#include <QPixmap>
#include <QMouseEvent>

#include "ClickableImage.hpp"

ClickableImage::ClickableImage(const QPoint& pos, const QPixmap& image, QWidget* parent)
	: QLabel(parent), m_Clicked(false)
{
	setPixmap(image);
	setGeometry(QRect(pos.x(), pos.y(), image.width(), image.height()));

	m_LastPoint = new QPoint();
}

ClickableImage::~ClickableImage()
{
	delete m_LastPoint;
}

void ClickableImage::mousePressEvent(QMouseEvent* e)
{
	*m_LastPoint = e->pos();
	m_Clicked = true;
}

void ClickableImage::mouseReleaseEvent(QMouseEvent* e)
{
	if (m_Clicked && (e->pos() == *m_LastPoint))
		emit clicked();
}


