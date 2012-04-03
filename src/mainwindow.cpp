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
#include "FilmwebSearch.hpp"
#include "ResultsModel.hpp"
#include "ResultsItem.hpp"

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

	setupCollection();
	setupResults();
	setupBrowser();
	setupFilters();

		preview = new QLineEdit(centralWidget);
		        preview->setObjectName(QString::fromUtf8("preview"));
		        preview->setGeometry(QRect(0, 650, 600, 20));

		    save = new QPushButton(centralWidget);
		        save->setObjectName(QString::fromUtf8("save"));
		        save->setGeometry(QRect(660, 650, 83, 24));
		       save->setText("Apply");

		connect(save, SIGNAL(clicked(bool)), this, SLOT(rename()));

	setupConnects();
}

void MainWindow::setupCollection()
{
	collectionModel = new CollectionModel(new CollectionItem, this);
	collectionModel->Update();

	collectionLabel = new QLabel(centralWidget);
	collectionLabel->setObjectName(QString::fromUtf8("collectionLabel"));
	collectionLabel->setGeometry(QRect(0, 0, 251, 16));
	collectionLabel->setText("Lokalna kolekcja");

	collectionListView = new QListView(centralWidget);
	collectionListView->setObjectName(QString::fromUtf8("collectionListView"));
	collectionListView->setGeometry(QRect(0, 20, 300, 300));
	collectionListView->setModel(collectionModel);

	collectionListView->setCurrentIndex(QModelIndex());
}

void MainWindow::setupResults()
{
	resultsModel = new ResultsModel(new ResultsItem, this);

    resultsLabel = new QLabel(centralWidget);
    resultsLabel->setObjectName(QString::fromUtf8("resultsLabel"));
    resultsLabel->setGeometry(QRect(0, 320, 301, 16));
    resultsLabel->setText("Wyniki wyszukiwania");

    resultsListView = new QListView(centralWidget);
    resultsListView->setObjectName(QString::fromUtf8("resultsListView"));
    resultsListView->setGeometry(QRect(0, 340, 301, 161));
    resultsListView->setModel(resultsModel);

    resultsListView->setCurrentIndex(QModelIndex());

    filmwebSearch = new FilmwebSearch(resultsModel);
}

void MainWindow::setupBrowser()
{
	filmwebLabel = new QLabel(centralWidget);
	filmwebLabel->setObjectName(QString::fromUtf8("filmwebLabel"));
	filmwebLabel->setGeometry(QRect(310, 0, 721, 16));
	filmwebLabel->setText("Podgląd na filmwebie");

	filmwebWebView = new QWebView(centralWidget);
	filmwebWebView->setObjectName(QString::fromUtf8("filmwebWebView"));
	filmwebWebView->setGeometry(QRect(310, 20, 711, 481));
	filmwebWebView->setUrl(QUrl("about:blank"));
}

void MainWindow::setupFilters()
{
}

void MainWindow::setupConnects()
{
	connect(collectionListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(collectionSelectionChanged(const QModelIndex &, const QModelIndex &)));
	connect(filmwebSearch, SIGNAL(queryFinished(bool)), this, SLOT(queryFinished(bool)));
	connect(filmwebSearch, SIGNAL(noResults()), resultsModel, SLOT(printEmpty()));
	//connect(group, SIGNAL(queryChanged(QStringList)), filmwebSearch, SLOT(queryChanged(QStringList)));
	connect(resultsListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(resultsSelectionChanged(const QModelIndex &, const QModelIndex &)));
}

void MainWindow::collectionSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
	 if (current.isValid())
	 {
		 collectionListView->setEnabled(false);
		 QString name = collectionModel->data(current, CollectionItem::NameRole).toString();

		 QStringList tokens = name.split(QRegExp("[^\\w']"), QString::SkipEmptyParts);
		 /*
		  * process with filtering
		  */

		 emit refresh_group(tokens);

		 filmwebWebView->load(QUrl("about:blank"));
		 preview->clear();

		 filmwebSearch->queryChanged(tokens);
	 }
}

void MainWindow::queryFinished(bool ok)
{
	resultsListView->setCurrentIndex(QModelIndex());

	collectionListView->setEnabled(true);

	if (!ok)
		resultsModel->printError();
}

void MainWindow::resultsSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
	if (current.isValid())
	{
		this->filmwebWebView->load(resultsModel->data(current, ResultsItem::URLRole).toString());

		QString newname = resultsModel->data(current, ResultsItem::TitleRole).toString();
		newname += " (" + resultsModel->data(current, ResultsItem::YearRole).toString() + ")";

		this->preview->setText(newname);
	}
}

void MainWindow::rename()
{
	QString path = collectionModel->data(collectionListView->currentIndex(), CollectionItem::PathRole).toString();

	QFile file(path);
	QFileInfo info(file);

	QString newpath = info.absoluteDir().absoluteFilePath(this->preview->text() + "." + info.completeSuffix());

	file.rename(newpath);

	collectionModel->Update();
}
