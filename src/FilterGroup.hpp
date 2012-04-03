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

		void append(QString text);

	public:
		FilterGroup(QWidget *parent = 0);
		~FilterGroup();

		void makeList(QStringList list);

		void clear();

	public slots:
		void onFilterStateChanged();

	signals:
		void queryChanged(QStringList);
};
