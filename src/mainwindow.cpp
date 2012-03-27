#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow()
{
	setupUi();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
}

void MainWindow::setupUi()
{
	this->resize(800, 600);

	centralWidget = new QWidget(this);
	centralWidget->setObjectName(QString::fromUtf8("centralwidget"));

	listView = new QListView(centralWidget);
	listView->setObjectName(QString::fromUtf8("listView"));
	listView->setGeometry(QRect(0, 0, 300, 300));

	this->setCentralWidget(centralWidget);
}
