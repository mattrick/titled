#pragma once

#include <QMainWindow>
#include <QtGui/QListView>
#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtWebKit/QWebView>

class QListViewItem;
class CollectionModel;

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 protected:
     void closeEvent(QCloseEvent *event);
     void setup();
     void setupCollection();
     void setupFilters();
     void setupBrowser();

 private slots:
 	 void zmiana_filmu(const QModelIndex & current, const QModelIndex & previous);

 private:
 	 QWidget *centralWidget;

 	CollectionModel *model;
 	 QListView *listView;


	QScrollArea *scrollArea;
	QWidget *scrollAreaWidgetContents;
	QWebView *m_Browser;

 };
