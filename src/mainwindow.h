#pragma once

#include <QMainWindow>
#include <QtGui/QListView>
#include <QtGui/QWidget>

 class MainWindow : public QMainWindow
 {
     Q_OBJECT

 public:
     MainWindow();

 protected:
     void closeEvent(QCloseEvent *event);
     void setupUi();

 private slots:

 private:
 	 QListView *listView;
 	 QWidget *centralWidget;

 };
