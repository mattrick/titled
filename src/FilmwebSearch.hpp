#pragma once

#include <QWebPage>
#include <QList>

class result;

class FilmwebSearch : public QWebPage
{
	Q_OBJECT

	private:
		QList<result*> *m_List;

	public:
		FilmwebSearch(QList<result*> *list, QObject * parent = 0);

	private slots:
		void queryLoadFinished();

	public slots:
		void queryChanged(QStringList tokens);

	signals:
		void queryStarted();
		void queryFinished();
};
