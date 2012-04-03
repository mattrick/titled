#include "FilterGroup.hpp"
#include "Filter.hpp"

#include <QDebug>

/*
 * TODO:
 *
 * Halt ongoing queries before emitting next signal (now it looks like some kind of buggy queue)
 *
 */

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

	onFilterStateChanged();
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

	connect(filter, SIGNAL(stateChanged()), this, SLOT(onFilterStateChanged()));
}

void FilterGroup::clear()
{
	m_Pos = 0;

	foreach (Filter* f, m_Filters)
	{
		disconnect(f, 0, this, 0);
		delete f;
	}

	m_Filters.clear();
}

void FilterGroup::onFilterStateChanged()
{
	QStringList list;

	foreach (Filter* f, m_Filters)
	{
		if (f->getState() == Filter::SEARCH)
			list.append(f->text());
	}

	emit queryChanged(list);

	/*list.clear();

	foreach (Filter* f, m_Filters)
	{
		if (f->getState() == Filter::ADD || f->getState() == Filter::INCLUDE)
			list.append(f->text());
	}

	emit extrasChanged(list);*/
}

QStringList FilterGroup::getExtras()
{
	QStringList list;

	foreach (Filter* f, m_Filters)
	{
		if (f->getState() == Filter::ADD || f->getState() == Filter::INCLUDE)
			list.append(f->text());
	}

	return list;
}
