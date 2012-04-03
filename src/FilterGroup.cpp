#include "FilterGroup.hpp"
#include "Filter.hpp"

#include <QDebug>

FilterGroup::FilterGroup(QWidget *parent)
	: QScrollArea(parent), m_Pos(0)
{
	contents = new QWidget(this);

	this->setFrameShape(QFrame::NoFrame);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setWidget(contents);
}

FilterGroup::~FilterGroup()
{
	clear();
}

void FilterGroup::makeList(QStringList list)
{
	clear();

	foreach (QString s, list)
	{
		append(s);
	}
}

void FilterGroup::append(QString text)
{
	Filter* filter = new Filter(text, contents);
	m_Filters.append(filter);
	QRect rect = filter->geometry();
	rect.moveLeft(m_Pos);
	filter->setGeometry(rect);
	m_Pos += rect.width();
	filter->show();

	contents->adjustSize();
}

void FilterGroup::clear()
{
	m_Pos = 0;

	qDeleteAll(m_Filters);

	m_Filters.clear();
}
