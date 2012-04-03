#include "Filter.hpp"
#include "WordDB.hpp"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include "ClickableImage.hpp"
#include <QDebug>

Filter::Filter(QString text, QWidget* parent)
	: QWidget(parent)
{
	lineEdit = new QLineEdit(this);
	lineEdit->setText(text);

	QFontMetrics fm = lineEdit->fontMetrics();
	lineEdit->resize(std::max(fm.width(text)+10, 50), 21);

	int x2 = (lineEdit->width() - 2*16 - 2) / 2;
	int x1 = (lineEdit->width() - 16) / 2;

	this->add = new ClickableImage(QPoint(x2, 21), QPixmap(":/images/add.png"), this);
	this->include = new ClickableImage(QPoint(x2 + 16 + 2, 21), QPixmap(":/images/include.png"), this);
	this->remove = new ClickableImage(QPoint(x2, 21 + 16 + 2), QPixmap(":/images/remove.png"), this);
	this->exclude = new ClickableImage(QPoint(x2 + 16 + 2, 21 + 16 + 2), QPixmap(":/images/exclude.png"), this);
	this->search = new ClickableImage(QPoint(x1, 21 + 2 * 16 + 2 * 2), QPixmap(":/images/search.png"), this);

	connect(add, SIGNAL(clicked()), this, SLOT(onClick()));

	setGeometry(QRect(0, 0, lineEdit->width() + 30, 21 + 5*16));
}

Filter::~Filter()
{

}
