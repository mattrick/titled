#include "Filter.hpp"
#include "WordDB.hpp"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>

#include "ClickableImage.hpp"
#include <QDebug>

Filter::Filter(QString text, QWidget* parent)
	: QWidget(parent), m_State(SEARCH)
{
	lineEdit = new QLineEdit(this);
	lineEdit->setText(text);

	QFontMetrics fm = lineEdit->fontMetrics();
	lineEdit->setGeometry(QRect(15, 0, std::max(fm.width(text)+10, 50), 21));

	int x2 = 15 + (lineEdit->width() - 2*16 - 2) / 2;
	int x1 = 15 + (lineEdit->width() - 16) / 2;

	this->add = new ClickableImage(QPoint(x2, 21), QPixmap(":/images/add.png"), this);
	this->include = new ClickableImage(QPoint(x2 + 16 + 2, 21), QPixmap(":/images/include.png"), this);
	this->remove = new ClickableImage(QPoint(x2, 21 + 16 + 2), QPixmap(":/images/remove.png"), this);
	this->exclude = new ClickableImage(QPoint(x2 + 16 + 2, 21 + 16 + 2), QPixmap(":/images/exclude.png"), this);
	this->search = new ClickableImage(QPoint(x1, 21 + 2 * 16 + 2 * 2), QPixmap(":/images/search.png"), this);

	connect(add, SIGNAL(clicked()), this, SLOT(onAddClick()));
	connect(include, SIGNAL(clicked()), this, SLOT(onIncludeClick()));
	connect(remove, SIGNAL(clicked()), this, SLOT(onRemoveClick()));
	connect(exclude, SIGNAL(clicked()), this, SLOT(onExcludeClick()));
	connect(search, SIGNAL(clicked()), this, SLOT(onSearchClick()));

	blockSignals(true);

	WordDB db;

	switch(db.Check(text.toStdString()))
	{
		case WordDB::White:
			setState(INCLUDE);
			break;

		case WordDB::Black:
			setState(EXCLUDE);
			break;
	}

	blockSignals(false);

	setGeometry(QRect(0, 0, lineEdit->width() + 30, 21 + 5*16));
}

Filter::~Filter()
{

}

void Filter::onAddClick()
{
	setState(ADD);
}

void Filter::onIncludeClick()
{
	setState(INCLUDE);
}

void Filter::onRemoveClick()
{
	setState(REMOVE);
}

void Filter::onExcludeClick()
{
	setState(EXCLUDE);
}

void Filter::onSearchClick()
{
	setState(SEARCH);
}

void Filter::setState(State state)
{
	if (state != m_State)
	{
		m_State = state;

		QPalette p(QApplication::palette());

		switch (state)
		{
			case SEARCH:
				lineEdit->setReadOnly(false);
				lineEdit->setEnabled(true);
				break;

			case ADD:
				lineEdit->setReadOnly(true);

				p.setColor(QPalette::Base, QColor(123, 255, 123));

				p.setColor(QPalette::Dark, QColor(0, 106, 0));
				p.setColor(QPalette::Light, QColor(63, 255, 63));
				p.setColor(QPalette::Window, QColor(0, 212, 0));

				break;

			case INCLUDE:
				lineEdit->setEnabled(false);

				p.setColor(QPalette::Base, Qt::green);
				break;

			case REMOVE:
				lineEdit->setReadOnly(true);

				p.setColor(QPalette::Base, QColor(255, 123, 123));

				p.setColor(QPalette::Dark, QColor(106, 0, 0));
				p.setColor(QPalette::Light, QColor(255, 63, 63));
				p.setColor(QPalette::Window, QColor(212, 0, 0));
				break;

			case EXCLUDE:
				lineEdit->setEnabled(false);

				p.setColor(QPalette::Base, Qt::red);
				break;
		}

		lineEdit->setPalette(p);

		emit changedState();
	}
}
