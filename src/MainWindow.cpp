#include <algorithm>
#include <type_traits>

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
#include <QApplication>

#include "Defaults.hpp"

#include "MainWindow.hpp"

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

	setupMenuBar();
	setupCollection();
	setupResults();
	setupBrowser();
	setupFilters();
	setupPreview();

	setupConnects();

}

void MainWindow::setupMenuBar()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	exitAction = fileMenu->addAction(tr("E&xit"));

	editMenu = menuBar()->addMenu(tr("&Edit"));
	settingsAction = editMenu->addAction(tr("&Settings"));
}

void MainWindow::setupCollection()
{
	collectionLabel = new QLabel(centralWidget);
	collectionLabel->setObjectName(QString::fromUtf8("collectionLabel"));
	collectionLabel->setGeometry(QRect(0, 0, 251, 16));
	collectionLabel->setText(tr("Local collection"));

	collectionListView = new QListView(centralWidget);
	collectionListView->setObjectName(QString::fromUtf8("collectionListView"));
	collectionListView->setGeometry(QRect(0, 20, 300, 300));

	collectionListView->setCurrentIndex(QModelIndex());
}

void MainWindow::setupResults()
{
    resultsLabel = new QLabel(centralWidget);
    resultsLabel->setObjectName(QString::fromUtf8("resultsLabel"));
    resultsLabel->setGeometry(QRect(0, 320, 301, 16));
    resultsLabel->setText(tr("Search results"));

    resultsListView = new QListView(centralWidget);
    resultsListView->setObjectName(QString::fromUtf8("resultsListView"));
    resultsListView->setGeometry(QRect(0, 340, 300, 250));

    //connect(resultsListView->horizontalScrollBar(), SIGNAL(valueChanged(int)), resultsListView->viewport(), SLOT(repaint()));

    resultsListView->setCurrentIndex(QModelIndex());
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

}

void MainWindow::setupPreview()
{
	previewEdit = new QLineEdit(centralWidget);
	previewEdit->setObjectName(QString::fromUtf8("previewEdit"));
	previewEdit->setGeometry(QRect(0, 728, 924, 20));

	saveButton = new QPushButton(centralWidget);
	saveButton->setObjectName(QString::fromUtf8("saveButton"));
	saveButton->setGeometry(QRect(924, 728, 100, 20));
	saveButton->setText(tr("Rename"));
}

void MainWindow::setupConnects()
{
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}
