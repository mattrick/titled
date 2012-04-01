#pragma once

#include <QWidget>

class Filter;
enum Action
	 {
		 ADD = 100,
		 REMOVE,
		 INCLUDE,
		 EXCLUDE,
		 SEARCH
	 };

class FilterGroup : public QWidget
{
	Q_OBJECT

private:
	QList<Filter*> m_Filters;

public:
	FilterGroup(int _x, int _y, QWidget * parent = 0, Qt::WindowFlags f = 0);

signals:
	void queryChanged(QString newquery);

public slots:
	void make(QStringList list);
		void update(Action action, QString text);

};
