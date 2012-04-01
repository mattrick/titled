#pragma once

#include <QMainWindow>
#include <QtGui/QListView>
#include <QtGui/QWidget>
#include <QtGui/QScrollArea>
#include <QtWebKit/QWebView>
#include <QStringList>
#include <QStringListModel>

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
 	 void item_changed(const QModelIndex & current, const QModelIndex & previous);
 	 void loading_finished();

public slots:
	void change_query(QString newquery);
	void result_changed_item(const QModelIndex & current, const QModelIndex & previous);

signals:
	void refresh_group(QStringList list);

 private:
 	 QWidget *centralWidget;

 	CollectionModel *model;
 	 QListView *listView;

 	 QListView *resultsList;
 	 QStringListModel* resultsModel;

 	FilterGroup* group;

 	QWebPage* page;
 	QWebFrame* frame;


	QScrollArea *scrollArea;
	QWidget *scrollAreaWidgetContents;
	QWebView *m_Browser;

 };
