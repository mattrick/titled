#pragma once

#include <QMainWindow>
#include <QtGui/QListView>
#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtWebKit/QWebView>
#include <QStringList>
#include <QStringListModel>
#include <QPushButton>
#include <QLabel>

class QListViewItem;
class CollectionModel;
class FilterGroup;
class FilmwebSearch;
class ResultsModel;
class CollectionListViewDelegate;
class ResultsListViewDelegate;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 protected:
     void closeEvent(QCloseEvent *event);
     void setup();
     void setupCollection();
     void setupResults();
     void setupBrowser();
     void setupFilters();
     void setupPreview();
     void setupConnects();

 private slots:
 	 void collectionSelectionChanged(const QModelIndex & current, const QModelIndex & previous);
 	 void queryFinished(bool ok);
 	void resultsSelectionChanged(const QModelIndex & current, const QModelIndex & previous);
 	void rename();
 	void onQueryChange(QStringList words);
 	void clearEverything();

 private:
		QWidget *centralWidget;

		CollectionModel *collectionModel;
		QListView *collectionListView;
		CollectionListViewDelegate *collectionListViewDelegate;
		QLabel *collectionLabel;

	    QLabel *resultsLabel;
	    QListView *resultsListView;
	    ResultsListViewDelegate *resultsListViewDelegate;
		ResultsModel* resultsModel;
		FilmwebSearch* filmwebSearch;
		FilterGroup* filterGroup;

		QLabel *filmwebLabel;
		QWebView *filmwebWebView;

		QLineEdit *previewEdit;
		QPushButton *saveButton;
 };
