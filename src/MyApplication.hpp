#pragma once

#include <QApplication>

class QModelIndex;
class QStringList;

class MainWindow;
class SettingsWindow;
class CollectionModel;
class ResultsModel;
class FilterGroup;
class Provider;

class MyApplication : public QApplication
{
	Q_OBJECT

	private:
		MainWindow* mainWin;

		SettingsWindow* settingsWindow;

		CollectionModel *collectionModel;

		ResultsModel* resultsModel;
		Provider* filmwebProvider;

		FilterGroup* filterGroup;

	public:
		MyApplication(int &argc, char **argv);

		void init();

		private slots:
		void collectionSelectionChanged(const QModelIndex & current);
		void queryFinished(int resultsCount);
		void resultsSelectionChanged(const QModelIndex & current);
		void rename();
		void onQueryChange(QStringList & words);
		void clearEverything();

		void openSettings();
		void onSettingsChanged();
		void onCountChanged(int count);
		void onTimeout();
};
