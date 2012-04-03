#pragma once

#include <QLabel>

class ClickableImage : public QLabel
{
    Q_OBJECT

	private:
		QPoint m_Point;
		bool m_Clicked;

protected:
    // re-implement processing of mouse events
    void mouseReleaseEvent ( QMouseEvent * e );
    void mousePressEvent ( QMouseEvent * e );

public:
    ClickableImage(QPoint pos, QPixmap image, QWidget* parent = 0);
    ~ClickableImage();

    signals:
        void clicked();
};
