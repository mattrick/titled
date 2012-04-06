#include <algorithm>

#include <QtGui>
#include <QString>
#include <QUrl>
#include <QWebFrame>
#include <QWebPage>
#include <QWebElement>
#include <QWebElementCollection>
#include <QNetworkCookie>
#include <QLabel>
#include <QFile>

#include "MainWindow.hpp"
#include "CollectionModel.hpp"
#include "CollectionItem.hpp"
#include "FilmwebSearch.hpp"
#include "ResultsModel.hpp"
#include "ResultsItem.hpp"
#include "CollectionListViewDelegate.hpp"
#include "ResultsListViewDelegate.hpp"
#include "FilterGroup.hpp"
#include "Filter.hpp"

/*
 * TODO:
 *
 * QFont::setPixelSize: Pixel size <= 0 (0)
 *
 */

MainWindow::MainWindow()
{
	setup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
}

void MainWindow::setup()
{
	this->resize(1024, 768);

	centralWidget = new QWidget(this);
	centralWidget->setObjectName(QString::fromUtf8("centralwidget"));

	this->setCentralWidget(centralWidget);

	setupCollection();
	setupResults();
	setupBrowser();
	setupFilters();
	setupPreview();

	setupConnects();
}

void MainWindow::setupCollection()
{
	collectionModel = new CollectionModel(new CollectionItem, this);
	collectionModel->Update();

	collectionLabel = new QLabel(centralWidget);
	collectionLabel->setObjectName(QString::fromUtf8("collectionLabel"));
	collectionLabel->setGeometry(QRect(0, 0, 251, 16));
	collectionLabel->setText(tr("Local collection"));

	collectionListView = new QListView(centralWidget);
	collectionListView->setObjectName(QString::fromUtf8("collectionListView"));
	collectionListView->setGeometry(QRect(0, 20, 300, 300));
	collectionListView->setModel(collectionModel);

	collectionListViewDelegate = new CollectionListViewDelegate();
	collectionListView->setItemDelegate(collectionListViewDelegate);

	collectionListView->setCurrentIndex(QModelIndex());
}

void MainWindow::setupResults()
{
	resultsModel = new ResultsModel(new ResultsItem, this);

    resultsLabel = new QLabel(centralWidget);
    resultsLabel->setObjectName(QString::fromUtf8("resultsLabel"));
    resultsLabel->setGeometry(QRect(0, 320, 301, 16));
    resultsLabel->setText(tr("Search results"));

    resultsListView = new QListView(centralWidget);
    resultsListView->setObjectName(QString::fromUtf8("resultsListView"));
    resultsListView->setGeometry(QRect(0, 340, 300, 250));
    resultsListView->setModel(resultsModel);

    resultsListViewDelegate = new ResultsListViewDelegate(resultsListView);
    resultsListView->setItemDelegate(resultsListViewDelegate);

    connect(resultsListView->horizontalScrollBar(), SIGNAL(valueChanged(int)), resultsListView->viewport(), SLOT(repaint()));

    resultsListView->setCurrentIndex(QModelIndex());

    filmwebSearch = new FilmwebSearch(resultsModel);
}

void MainWindow::setupBrowser()
{
	filmwebLabel = new QLabel(centralWidget);
	filmwebLabel->setObjectName(QString::fromUtf8("filmwebLabel"));
	filmwebLabel->setGeometry(QRect(310, 0, 721, 16));
	filmwebLabel->setText(tr("Preview on filmweb"));

	filmwebWebView = new QWebView(centralWidget);
	filmwebWebView->setObjectName(QString::fromUtf8("filmwebWebView"));
	filmwebWebView->setGeometry(QRect(310, 20, 714, 570));
	filmwebWebView->setUrl(QUrl("about:blank"));

	QList<QNetworkCookie> cookies;

	QNetworkCookie cookie(QByteArray("welcomeScreen"),QByteArray("welcome_screen"));
	cookies.append(cookie);

	filmwebWebView->page()->networkAccessManager()->cookieJar()->setCookiesFromUrl(cookies, QUrl("http://www.filmweb.pl"));
}

void MainWindow::setupFilters()
{
	filterGroup = new FilterGroup(centralWidget);
	filterGroup->setGeometry(QRect(0, 640, 1024, 100));
}

void MainWindow::setupPreview()
{
	previewEdit = new QLineEdit(centralWidget);
	previewEdit->setObjectName(QString::fromUtf8("previewEdit"));
	previewEdit->setGeometry(QRect(0, 748, 924, 20));

	saveButton = new QPushButton(centralWidget);
	saveButton->setObjectName(QString::fromUtf8("saveButton"));
	saveButton->setGeometry(QRect(924, 748, 100, 20));
	saveButton->setText(tr("Rename"));
}

void MainWindow::setupConnects()
{
	connect(collectionListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(collectionSelectionChanged(const QModelIndex &, const QModelIndex &)));
	connect(filmwebSearch, SIGNAL(queryFinished(bool)), this, SLOT(queryFinished(bool)));
	connect(filmwebSearch, SIGNAL(noResults()), resultsModel, SLOT(printEmpty()));
	connect(filterGroup, SIGNAL(queryChanged(QStringList)), this, SLOT(onQueryChange(QStringList)));
	connect(resultsListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(resultsSelectionChanged(const QModelIndex &, const QModelIndex &)));
	connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(rename()));
}

void MainWindow::collectionSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
	 if (current.isValid())
	 {
		 collectionListView->setEnabled(false);
		 filterGroup->setEnabled(false);
		 QString name = collectionModel->data(current, CollectionItem::NameRole).toString();

		 QStringList tokens = name.split(QRegExp("[^\\w']"), QString::SkipEmptyParts);

		 filterGroup->makeList(tokens);

		 filmwebWebView->load(QUrl("about:blank"));
		 previewEdit->clear();
	 }
}

void MainWindow::queryFinished(bool ok)
{
	resultsListView->setCurrentIndex(QModelIndex());

	collectionListView->setEnabled(true);
	filterGroup->setEnabled(true);

	if (!ok)
		resultsModel->printError();
}

/*
 * TODO:
 *
 * Custom saving scheme
 *
 */

void MainWindow::resultsSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
	if (current.isValid())
	{
		filmwebWebView->load(resultsModel->data(current, ResultsItem::URLRole).toString());

		QString newname = resultsModel->data(current, ResultsItem::TitleRole).toString();
		newname += " (" + resultsModel->data(current, ResultsItem::YearRole).toString() + ")";

		if (!filterGroup->getExtras().empty())
			newname += " " + filterGroup->getExtras().join(".");

		previewEdit->setText(newname);
	}
}

void MainWindow::onQueryChange(QStringList words)
{
	filmwebSearch->queryChanged(words);
	resultsModel->clear();
}

void MainWindow::rename()
{
	QString path = collectionModel->data(collectionListView->currentIndex(), CollectionItem::PathRole).toString();

	QFile file(path);
	QFileInfo info(file);

	QString newpath = info.absoluteDir().absoluteFilePath(previewEdit->text() + "." + info.completeSuffix());

	file.rename(newpath);

	collectionModel->Update();

	clearEverything();
}

void MainWindow::clearEverything()
{
	collectionListView->setCurrentIndex(QModelIndex());

	resultsModel->clear();
	resultsListView->setCurrentIndex(QModelIndex());

	filterGroup->clear();

	filmwebWebView->load(QUrl("about:blank"));

	previewEdit->clear();
}
