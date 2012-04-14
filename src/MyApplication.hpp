#pragma once

#include <QApplication>
#include <QSettings>
#include <QTextCodec>

#include "Defaults.hpp"

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
#include "SettingsWidget.hpp"
#include "InfoDelegate.hpp"
#include "InfoItem.hpp"

class MyApplication : public QApplication
{
	Q_OBJECT

	private:
		MainWindow* mainWin;

		SettingsWidget* settingsWidget;

		CollectionModel *collectionModel;

		ResultsModel* resultsModel;
		FilmwebSearch* filmwebSearch;

		FilterGroup* filterGroup;

	public:
		MyApplication(int &argc, char **argv)
			: QApplication(argc, argv)
		{
			setOrganizationName("mattrick");
			setOrganizationDomain("mattrick");
			setApplicationName("titled");
			setApplicationVersion("0.3");

			QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
			QSettings::setDefaultFormat(QSettings::IniFormat);

			init();
		}

		void init()
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
			connect(filterGroup, SIGNAL(queryChanged(QStringList)), this, SLOT(onQueryChange(QStringList)));

			connect(collectionModel, SIGNAL(countChanged(int)), this, SLOT(onCountChanged(int)));

			connect(mainWin->collectionListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(collectionSelectionChanged(const QModelIndex &, const QModelIndex &)));
				connect(mainWin->resultsListView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(resultsSelectionChanged(const QModelIndex &, const QModelIndex &)));
				connect(mainWin->saveButton, SIGNAL(clicked(bool)), this, SLOT(rename()));

				connect(mainWin->settingsAction, SIGNAL(triggered()), this, SLOT(openSettings()));

			collectionModel->Update();

			//

			mainWin->setWindowTitle(QApplication::applicationName()+" v"+QApplication::applicationVersion());
			mainWin->show();
		}

		private slots:
		void collectionSelectionChanged(const QModelIndex & current, const QModelIndex & previous);
		void queryFinished(bool ok);
		void resultsSelectionChanged(const QModelIndex & current, const QModelIndex & previous);
		void rename();
		void onQueryChange(QStringList words);
		void clearEverything();

		void openSettings();
		void onSettingsChanged();
		void onCountChanged(int count);
		void onNoResults();
};
