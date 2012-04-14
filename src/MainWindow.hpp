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
#include <QMenuBar>
#include <QAction>

class QListViewItem;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		QWidget *centralWidget;

		QMenu* fileMenu;
		QAction* exitAction;

		QMenu* editMenu;
		QAction* settingsAction;

		QListView *collectionListView;
		QLabel *collectionLabel;

		QLabel *resultsLabel;
		QListView *resultsListView;

		QLabel *filmwebLabel;
		QWebView *filmwebWebView;

		QLineEdit *previewEdit;
		QPushButton *saveButton;

	protected:
		void closeEvent(QCloseEvent *event);
		void setup();
		void setupMenuBar();
		void setupCollection();
		void setupResults();
		void setupBrowser();
		void setupFilters();
		void setupPreview();
		void setupConnects();

	public:
		MainWindow();
 };
