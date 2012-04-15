 #include "FilmwebProvider.hpp"

#include <QtPlugin>

#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QWebElementCollection>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QTimer>
#include <QAction>

FilmwebProvider::FilmwebProvider(ResultsModel* model, QObject* parent)
	: resultsModel(model)
{
	webPage = new QWebPage(this);

	connect(webPage->mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(queryLoadFinished(bool)));

	QList<QNetworkCookie> cookies;

	QNetworkCookie cookie(QByteArray("welcomeScreen"),QByteArray("welcome_screen"));
	cookies.append(cookie);

	webPage->networkAccessManager()->cookieJar()->setCookiesFromUrl(cookies, QUrl("http://www.filmweb.pl"));

	timeout = new QTimer();
	connect(timeout, SIGNAL(timeout()), webPage->action(webPage->Stop), SLOT(trigger()));
}

void FilmwebProvider::query(const QStringList & tokens)
{
	emit queryStarted();

	resultsModel->clear();

	QUrl queryUrl("http://www.filmweb.pl/search?q=" + tokens.join("+"));

	webPage->mainFrame()->load(queryUrl);

	timeout->start(5000);
}

void FilmwebProvider::queryLoadFinished(bool ok)
{
	timeout->stop();

	if (ok)
	{
		QWebElement document = webPage->mainFrame()->documentElement();

		QWebElementCollection links = document.findAll("li.searchResult");
		foreach (QWebElement e, links)
		{
			if (e.findFirst("span.searchResultTypeAlias").toPlainText() == "film" || e.findFirst("span.searchResultTypeAlias").toPlainText() == "TV")
			{
				QString plainName = e.findFirst("a.searchResultTitle").toPlainText();

				QStringList name = plainName.split(QRegExp(" / "), QString::SkipEmptyParts);

				QString plainDetails = e.findFirst("div.searchResultDetails").toPlainText();
				QStringList details = plainDetails.split(QRegExp(" | "), QString::SkipEmptyParts);

				resultsModel->appendRow(new ResultsItem(name[0], (name.size() > 1) ? (name[1]) : (QString("")), details[0], "http://www.filmweb.pl" + e.findFirst("a.searchResultTitle").attribute("href")));
			}
		}
	}
	else
		emit queryTimeout();

	emit queryFinished(resultsModel->rowCount());
}

 Provider* FilmwebProviderFactory::GetProvider(ResultsModel* model, QObject* parent)
 {
     return new FilmwebProvider(model, parent);
 }

 Q_EXPORT_PLUGIN2(FilmwebProvider, FilmwebProviderFactory);
