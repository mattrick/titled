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

	public:
		enum State
		{
			SEARCH = 0,
			ADD,
			INCLUDE,
			REMOVE,
			EXCLUDE
		};

	private:
		State m_State;

		QLineEdit *lineEdit;
		ClickableImage *add;
		ClickableImage *include;
		ClickableImage *remove;
		ClickableImage *exclude;
		ClickableImage *search;

	private slots:
		void onAddClick();
		void onIncludeClick();
		void onRemoveClick();
		void onExcludeClick();
		void onSearchClick();

	protected:

	public:
		Filter(QString text, QWidget* parent = 0);
		~Filter();

	public slots:
		void setState(State state);

	signals:
		void changedState();
};
