#pragma once

#include <QMainWindow>

class QWidget;
class QMenu;
class QAction;
class QListView;
class QLineEdit;
class QLabel;
class QWebView;
class QPushButton;
class QCloseEvent;

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
