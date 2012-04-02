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

class result
	 {
	 public:
		 QString title;
		 QString original;
		 QUrl url;
		 QString year;
	 };


QList<result*> results;

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

	group = new FilterGroup(0, 600, this);

	connect(this, SIGNAL(refresh_group(QStringList)), group, SLOT(make(QStringList)));

	connect(group, SIGNAL(queryChanged(QString)), this, SLOT(change_query(QString)));



	//setupFilters();

		collectionListView->selectionModel()->setObjectName("SelectionModel");



		connect(collectionListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(item_changed(const QModelIndex &, const QModelIndex &)));
		connect(resultsListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(result_changed_item(const QModelIndex &, const QModelIndex &)));

		preview = new QLineEdit(centralWidget);
		        preview->setObjectName(QString::fromUtf8("preview"));
		        preview->setGeometry(QRect(0, 650, 600, 20));

		    save = new QPushButton(centralWidget);
		        save->setObjectName(QString::fromUtf8("save"));
		        save->setGeometry(QRect(660, 650, 83, 24));
		       save->setText("Apply");

		connect(save, SIGNAL(clicked(bool)), this, SLOT(rename()));

		//temp
		connect(filmwebSearch, SIGNAL(queryFinished()), this, SLOT(loading_finished()));
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
}

void MainWindow::setupResults()
{
	resultsModel = new QStringListModel();

    resultsLabel = new QLabel(centralWidget);
    resultsLabel->setObjectName(QString::fromUtf8("resultsLabel"));
    resultsLabel->setGeometry(QRect(0, 320, 301, 16));
    resultsLabel->setText("Wyniki wyszukiwania");

    resultsListView = new QListView(centralWidget);
    resultsListView->setObjectName(QString::fromUtf8("resultsListView"));
    resultsListView->setGeometry(QRect(0, 340, 301, 161));
    resultsListView->setModel(resultsModel);

    filmwebSearch = new FilmwebSearch(&results);
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
	filmwebLabel = new QLabel(centralWidget);
	filmwebLabel->setObjectName(QString::fromUtf8("filmwebLabel"));
	filmwebLabel->setGeometry(QRect(310, 0, 721, 16));
	filmwebLabel->setText("Podgląd na filmwebie");

	filmwebWebView = new QWebView(centralWidget);
	filmwebWebView->setObjectName(QString::fromUtf8("filmwebWebView"));
	filmwebWebView->setGeometry(QRect(310, 20, 711, 481));
	filmwebWebView->setUrl(QUrl("about:blank"));
}



void MainWindow::item_changed(const QModelIndex & current, const QModelIndex & previous)
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

		 change_query(tokens.join("+"));
	 }

}

void MainWindow::change_query(QString newquery)
{
	qDebug() << "change";
	 filmwebSearch->queryChanged(newquery.split("+"));
}

void MainWindow::loading_finished()
{
	collectionListView->setEnabled(true);

	 QStringList list;

	 foreach(result* r, results)
	 {
		 list.append(r->title);
	 }
	 resultsModel->setStringList(list);

}

void MainWindow::result_changed_item(const QModelIndex & current, const QModelIndex & previous)
{
	result* r = results.at(current.row());
	this->filmwebWebView->load(r->url);

	QString newname = r->title + " (" + r->year + ")";

	this->preview->setText(newname);
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
