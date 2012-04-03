#pragma once

#include <QScrollArea>
#include <QList>

class Filter;

class FilterGroup : public QScrollArea
{
	Q_OBJECT

	private:
		QWidget* contents;

		QList<Filter*> m_Filters;

		int m_Pos;

	public:
		FilterGroup(QWidget *parent = 0);
		~FilterGroup();

		void append(QString text);
		void makeList(QStringList list);

		void clear();
};
