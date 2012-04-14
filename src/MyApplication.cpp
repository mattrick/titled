#include <QSettings>
#include <QListView>
#include <QString>
#include <QPushButton>
#include <QAction>
#include <QWebView>
#include <QLineEdit>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>

#include "MyApplication.hpp"
#include "Defaults.hpp"
#include "MainWindow.hpp"
#include "CollectionModel.hpp"
#include "ResultsModel.hpp"
#include "ResultsItem.hpp"
#include "FilmwebSearch.hpp"
#include "FilterGroup.hpp"
#include "CollectionItem.hpp"
#include "InfoDelegate.hpp"
#include "InfoItem.hpp"
#include "ResultsListViewDelegate.hpp"
#include "SettingsWindow.hpp"
#include "CollectionListViewDelegate.hpp"

MyApplication::MyApplication(int & argc, char * * argv)
	: QApplication(argc, argv)
{
	setOrganizationName("mattrick");
	setOrganizationDomain("mattrick");
	setApplicationName("titled");
	setApplicationVersion("0.3");

	//QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QSettings::setDefaultFormat(QSettings::IniFormat);

	init();
}

void MyApplication::init()
{
	mainWin = new MainWindow;

	//

	collectionModel = new CollectionModel(this);

	mainWin->collectionListView->setModel(collectionModel);

	resultsModel = new ResultsModel(this);

	mainWin->resultsListView->setModel(resultsModel);

	filmwebSearch = new FilmwebSearch(resultsModel);

	filterGroup = new FilterGroup(mainWin->centralWidget);
	filterGroup->setGeometry(QRect(0, 620, 1024, 100));


	connect(filmwebSearch, SIGNAL(queryFinished(bool)), this, SLOT(queryFinished(bool)));
	connect(filmwebSearch, SIGNAL(noResults()), this, SLOT(onNoResults()));
	connect(filterGroup, SIGNAL(queryChanged(QStringList&)), this, SLOT(onQueryChange(QStringList&)));

	connect(collectionModel, SIGNAL(countChanged(int)), this, SLOT(onCountChanged(int)));

	connect(mainWin->collectionListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(collectionSelectionChanged(const QModelIndex &)));
	connect(mainWin->resultsListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(resultsSelectionChanged(const QModelIndex &)));
	connect(mainWin->saveButton, SIGNAL(clicked(bool)), this, SLOT(rename()));

	connect(mainWin->settingsAction, SIGNAL(triggered()), this, SLOT(openSettings()));

	collectionModel->Update();

	//

	mainWin->setWindowTitle(QApplication::applicationName()+" v"+QApplication::applicationVersion());
	mainWin->show();
}


void MyApplication::collectionSelectionChanged(const QModelIndex & current)
{
	 if (current.isValid())
	 {
		 mainWin->collectionListView->setEnabled(false);
		 filterGroup->setEnabled(false);
		 QString name = collectionModel->data(current, CollectionItem::NameRole).toString();

		 QStringList tokens = name.split(QRegExp("[^\\w']"), QString::SkipEmptyParts);

		 filterGroup->makeList(tokens);

		 mainWin->filmwebWebView->load(QUrl("about:blank"));
		 mainWin->previewEdit->clear();
	 }
}


void MyApplication::queryFinished(bool ok)
{
	mainWin->resultsListView->setCurrentIndex(QModelIndex());

	mainWin->collectionListView->setEnabled(true);
	filterGroup->setEnabled(true);

	if (!ok)
	{
		resultsModel->clear();

		mainWin->resultsListView->setItemDelegate(new InfoDelegate(mainWin->resultsListView));

		resultsModel->appendRow(new InfoItem(tr("Error fetching search results"), tr("query timeout")));
	}
}

/*
 * TODO:
 *
 * Custom saving scheme
 *
 */

void MyApplication::resultsSelectionChanged(const QModelIndex & current)
{
	if (current.isValid())
	{
		mainWin->filmwebWebView->load(resultsModel->data(current, ResultsItem::URLRole).toString());

		QString newname = resultsModel->data(current, ResultsItem::TitleRole).toString();
		newname += " (" + resultsModel->data(current, ResultsItem::YearRole).toString() + ")";

		if (!filterGroup->getExtras().empty())
			newname += " " + filterGroup->getExtras().join(".");

		mainWin->previewEdit->setText(newname);
	}
}

void MyApplication::onQueryChange(QStringList & words)
{
	filmwebSearch->queryChanged(words);
	resultsModel->clear();

	mainWin->resultsListView->setItemDelegate(new ResultsListViewDelegate(mainWin->resultsListView));
}

void MyApplication::rename()
{
	QString path = collectionModel->data(mainWin->collectionListView->currentIndex(), CollectionItem::PathRole).toString();

	QFile file(path);
	QFileInfo info(file);

	QString newpath = info.absoluteDir().absoluteFilePath(mainWin->previewEdit->text() + "." + info.completeSuffix());

	file.rename(newpath);

	collectionModel->Update();

	clearEverything();
}

void MyApplication::clearEverything()
{
	mainWin->collectionListView->setCurrentIndex(QModelIndex());

	resultsModel->clear();
	mainWin->resultsListView->setCurrentIndex(QModelIndex());

	filterGroup->clear();

	mainWin->filmwebWebView->load(QUrl("about:blank"));

	mainWin->previewEdit->clear();
}

void MyApplication::openSettings()
{
	settingsWindow = new SettingsWindow();
	settingsWindow->show();

	connect(settingsWindow, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));
}

void MyApplication::onSettingsChanged()
{
	collectionModel->Rebuild();
}

void MyApplication::onCountChanged(int count)
{
	if (count)
	{
		if (!std::is_same<decltype(mainWin->collectionListView->itemDelegate()), CollectionListViewDelegate>::value)
			mainWin->collectionListView->setItemDelegate(new CollectionListViewDelegate(mainWin->collectionListView));
	}
	else
	{
		mainWin->collectionListView->setItemDelegate(new InfoDelegate(mainWin->collectionListView));
		collectionModel->appendRow(new InfoItem("Your collection is empty!", "visit settings"));
	}
}

void MyApplication::onNoResults()
{
	resultsModel->clear();

	mainWin->resultsListView->setItemDelegate(new InfoDelegate(mainWin->resultsListView));

	resultsModel->appendRow(new InfoItem(tr("No matching titles"), "change your query"));
}
