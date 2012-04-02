#include "FilmwebSearch.hpp"

#include <QWebFrame>
#include <QWebElement>
#include <QWebElementCollection>
#include <QNetworkCookie>

class result
	 {
	 public:
		 QString title;
		 QString original;
		 QUrl url;
		 QString year;
	 };

FilmwebSearch::FilmwebSearch(QList<result*> *list, QObject * parent)
	: m_List(list), QWebPage(parent)
{
	connect(mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(queryLoadFinished()));

	QList<QNetworkCookie> cookies;

	QNetworkCookie cookie(QByteArray("welcomeScreen"),QByteArray("welcome_screen"));
	cookies.append(cookie);

	networkAccessManager()->cookieJar()->setCookiesFromUrl(cookies, QUrl("https://www.filmweb.pl"));
}

void FilmwebSearch::queryChanged(QStringList tokens)
{
	emit queryStarted();

	QUrl queryUrl("http://www.filmweb.pl/search?q=" + tokens.join("+"));

	mainFrame()->load(queryUrl);
}

void FilmwebSearch::queryLoadFinished()
{
	QWebElement document = mainFrame()->documentElement();

	QWebElementCollection links = document.findAll("li.searchResult");
	foreach (QWebElement e, links)
	{
		if (e.findFirst("span.searchResultTypeAlias").toPlainText() == "film" || e.findFirst("span.searchResultTypeAlias").toPlainText() == "TV")
		{
			QString plainName = e.findFirst("a.searchResultTitle").toPlainText();

			QStringList name = plainName.split(QRegExp(" / "), QString::SkipEmptyParts);
			result *r = new result();
			r->title = name[0];
			if (name.size() > 1)
			 r->original = name[1];

			QString plainDetails = e.findFirst("div.searchResultDetails").toPlainText();
			QStringList details = plainDetails.split(QRegExp(" | "), QString::SkipEmptyParts);

			r->year = details[0];

			r->url = "http://www.filmweb.pl" + e.findFirst("a.searchResultTitle").attribute("href");
			m_List->append(r);
		}
	}

	emit queryFinished();
}
