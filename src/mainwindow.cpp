#include <algorithm>

#include <QtGui>
#include <QString>
#include <QDebug>
#include <QUrl>
#include <QWebFrame>
#include <QWebPage>
#include <QWebElement>
#include <QWebElementCollection>
#include <QNetworkCookie>
#include <QLabel>
#include <QFile>

#include "mainwindow.h"
#include "CollectionModel.hpp"
#include "CollectionItem.hpp"

MainWindow::MainWindow()
{
	setup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
}

#include "FilterGroup.hpp"

void MainWindow::setup()
{
	this->setObjectName("okno");
	this->resize(1024, 768);

	centralWidget = new QWidget(this);
	centralWidget->setObjectName(QString::fromUtf8("centralwidget"));

	this->setCentralWidget(centralWidget);

	QStringList tokens = QString("fsa fsa fxzf qw rq").split(" ");

	group = new FilterGroup(0, 600, this);

	connect(this, SIGNAL(refresh_group(QStringList)), group, SLOT(make(QStringList)));

	connect(group, SIGNAL(queryChanged(QString)), this, SLOT(change_query(QString)));

	resultsList = new QListView(centralWidget);
			resultsList->setObjectName(QString::fromUtf8("resultsList"));
			resultsList->setGeometry(QRect(0, 350, 300, 200));

		resultsModel = new QStringListModel();

		resultsList->setModel(resultsModel);

	setupCollection();
	setupBrowser();
	//setupFilters();
}

void MainWindow::setupCollection()
{
	listView = new QListView(centralWidget);
	listView->setObjectName(QString::fromUtf8("listView"));
	listView->setGeometry(QRect(0, 0, 300, 300));

	model = new CollectionModel(new CollectionItem, this);

	model->Update();

	listView->setModel(model);
	listView->setObjectName("listView");

	page = new QWebPage(this);
	//page->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
	frame = page->mainFrame();
	frame->setObjectName("frame");
	listView->selectionModel()->setObjectName("SelectionModel");

	 QList<QNetworkCookie> cookies;
		     QNetworkCookie cookie(QByteArray("welcomeScreen"),QByteArray("welcome_screen"));
		     cookies.append(cookie);

		 page->networkAccessManager()->cookieJar()->setCookiesFromUrl(cookies, QUrl("https://www.filmweb.pl"));

	connect(listView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(item_changed(const QModelIndex &, const QModelIndex &)));
	connect(resultsList->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(result_changed_item(const QModelIndex &, const QModelIndex &)));
	connect(frame, SIGNAL(loadFinished(bool)), this, SLOT(loading_finished()));

	preview = new QLineEdit(centralWidget);
	        preview->setObjectName(QString::fromUtf8("preview"));
	        preview->setGeometry(QRect(0, 650, 600, 20));

	    save = new QPushButton(centralWidget);
	        save->setObjectName(QString::fromUtf8("save"));
	        save->setGeometry(QRect(660, 650, 83, 24));
	       save->setText("Apply");

	connect(save, SIGNAL(clicked(bool)), this, SLOT(rename()));
}

void MainWindow::setupFilters()
{
	scrollArea = new QScrollArea(centralWidget);
	        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
	        scrollArea->setGeometry(QRect(0, 524, 661, 71));
	        //scrollArea->setFrameShape(QFrame::NoFrame);
	        scrollArea->setWidgetResizable(true);
	        scrollAreaWidgetContents = new QWidget();
	        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
	        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 661, 71));

	        scrollArea->setWidget(scrollAreaWidgetContents);
}

void MainWindow::setupBrowser()
{
	m_Browser = new QWebView(centralWidget);
	m_Browser->setObjectName(QString::fromUtf8("m_Browser"));
	m_Browser->setGeometry(QRect(384, 0, 640, 480));
	m_Browser->setUrl(QUrl("about:blank"));
}



void MainWindow::item_changed(const QModelIndex & current, const QModelIndex & previous)
{
	 if (current.isValid())
	 {
		 listView->setEnabled(false);
		 QString name = model->data(current, CollectionItem::NameRole).toString();

		 QStringList tokens = name.split(QRegExp("[^\\w']"), QString::SkipEmptyParts);
		 /*
		  * process with filtering
		  */

		 emit refresh_group(tokens);

		 change_query(tokens.join("+"));
	 }

}

void MainWindow::change_query(QString newquery)
{
	 QUrl query ("http://www.filmweb.pl/search?q=" + newquery);

	 frame->load(query);
}

class result
	 {
	 public:
		 QString title;
		 QString original;
		 QUrl url;
		 QString year;
	 };


QList<result> results;


void MainWindow::loading_finished()
{
	results.clear();
	listView->setEnabled(true);


	 QWebElement document = page->mainFrame()->documentElement();
	 QWebElementCollection links = document.findAll("li.searchResult");
	 foreach (QWebElement e, links) {
		if (e.findFirst("span.searchResultTypeAlias").toPlainText() == "film" || e.findFirst("span.searchResultTypeAlias").toPlainText() == "TV")
		{
			QString plainName = e.findFirst("a.searchResultTitle").toPlainText();

		 QStringList name = plainName.split(QRegExp(" / "), QString::SkipEmptyParts);
		 result r;
		 r.title = name[0];
		 if (name.size() > 1)
			 r.original = name[1];

		 QString plainDetails = e.findFirst("div.searchResultDetails").toPlainText();
		 QStringList details = plainDetails.split(QRegExp(" | "), QString::SkipEmptyParts);

		 r.year = details[0];

		 r.url = "http://www.filmweb.pl" + e.findFirst("a.searchResultTitle").attribute("href");
		 results.append(r);
		}
	 }

	 QStringList list;

	 foreach(result r, results)
	 {
		 list.append(r.title);
	 }
	 resultsModel->setStringList(list);
}

void MainWindow::result_changed_item(const QModelIndex & current, const QModelIndex & previous)
{
	result r = results.at(current.row());
	this->m_Browser->load(r.url);

	QString newname = r.title + " (" + r.year + ")";

	this->preview->setText(newname);
}

void MainWindow::rename()
{
	QString path = model->data(listView->currentIndex(), CollectionItem::PathRole).toString();

	QFile file(path);
	QFileInfo info(file);

	QString newpath = info.absoluteDir().absoluteFilePath(this->preview->text() + "." + info.completeSuffix());

	file.rename(newpath);

	model->Update();
}
