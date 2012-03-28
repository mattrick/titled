#pragma once

#include <QMainWindow>
#include <QtGui/QListView>
#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtWebKit/QWebView>
#include <QStringList>

class QListViewItem;
class CollectionModel;
class FilterGroup;

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
 	 void koniec_ladowania();

signals:
	void refresh_group(QStringList list);

 private:
 	 QWidget *centralWidget;

 	CollectionModel *model;
 	 QListView *listView;

 	FilterGroup* group;

 	QWebPage* page;


	QScrollArea *scrollArea;
	QWidget *scrollAreaWidgetContents;
	QWebView *m_Browser;

 };
