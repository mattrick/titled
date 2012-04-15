#pragma once

 #include <QObject>
#include "FilmwebProvider.hpp"

#include "Provider.hpp"

class QWebPage;
class QTimer;
class ResultsModel;

class FilmwebProvider : public Provider
{
	Q_OBJECT

	private:
		ResultsModel* resultsModel;
		QTimer* timeout;
		QWebPage* webPage;

	protected:

	public:
		FilmwebProvider(ResultsModel* model, QObject* parent = 0);

	private slots:
		void queryLoadFinished(bool ok = false);

	public slots:
		void query(const QStringList& tokens);

	public:
		QString name() const { return "EchoProvider"; }

};

class FilmwebProviderFactory : public QObject, ProviderFactory
{
	Q_OBJECT
	Q_INTERFACES(ProviderFactory)

	private:

	protected:

	public:
		virtual Provider* GetProvider(ResultsModel* model, QObject* parent = 0);
};
