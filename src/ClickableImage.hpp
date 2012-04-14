#pragma once

#include <QLabel>

class ClickableImage : public QLabel
{
	Q_OBJECT

	private:
		QPoint* m_LastPoint;
		bool m_Clicked;

	protected:
		void mouseReleaseEvent(QMouseEvent* e);
		void mousePressEvent(QMouseEvent* e);

	public:
		ClickableImage(const QPoint& pos, const QPixmap& image, QWidget* parent = 0);
		virtual~ClickableImage();

	signals:
		void clicked();
};
