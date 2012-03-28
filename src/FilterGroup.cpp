#include "FilterGroup.hpp"
#include "Filter.hpp"

#include <QDebug>

FilterGroup::FilterGroup(int _x, int _y, QWidget * parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{

	setGeometry(_x, _y, parent->width(), 60);
}

void FilterGroup::make(QStringList list)
{
	foreach (Filter* f, m_Filters)
	{
		delete f;
	}
	m_Filters.clear();

	int x = 0;

	foreach(QString s, list)
	{
		m_Filters.append(new Filter(s, x, 0, this));
		x += m_Filters.back()->width() + 50;
		m_Filters.back()->show();
	}

}

void FilterGroup::update(Action action, QString text)
{
	qDebug() << text;
}
