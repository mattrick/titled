#pragma once

#include <QWidget>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class WordDB;
class ClickableImage;

class Filter : public QWidget
{
	Q_OBJECT

	private:
		QLineEdit *lineEdit;
		ClickableImage *add;
		ClickableImage *include;
		ClickableImage *remove;
		ClickableImage *exclude;
		ClickableImage *search;

	protected:

	public:
		Filter(QString text, QWidget* parent = 0);
		~Filter();
};
