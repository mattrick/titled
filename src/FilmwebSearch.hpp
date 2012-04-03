#pragma once

#include <QWebPage>
#include <QTimer>

class ResultsModel;
class ResultsItem;

class FilmwebSearch : public QWebPage
{
	Q_OBJECT

	private:
		ResultsModel* resultsModel;
		QTimer* timeout;

	public:
		FilmwebSearch(ResultsModel* model, QObject * parent = 0);

	private slots:
		void queryLoadFinished(bool ok = false);

	public slots:
		void queryChanged(QStringList tokens);

	signals:
		void queryStarted();
		void queryFinished(bool);
		void noResults();
};
