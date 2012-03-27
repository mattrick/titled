#include <algorithm>

#include <QtGui>
#include <QString>

#include "mainwindow.h"
#include "Collection.hpp"
#include "CollectionModel.hpp"
#include "CollectionItem.hpp"

MainWindow::MainWindow()
{
	setup();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
}

void MainWindow::setup()
{
	this->resize(800, 600);

	centralWidget = new QWidget(this);
	centralWidget->setObjectName(QString::fromUtf8("centralwidget"));

	this->setCentralWidget(centralWidget);

	setupCollection();
}

void MainWindow::setupCollection()
{
	listView = new QListView(centralWidget);
	listView->setObjectName(QString::fromUtf8("listView"));
	listView->setGeometry(QRect(0, 0, 400, 300));

	CollectionModel *model = new CollectionModel(new CollectionItem, this);

	Collection collection("collection");
	collection.Build();

	auto lista = collection.GetList();

	for_each(lista.begin(), lista.end(), [&model](CollectionEntry entry){
			model->appendRow(new CollectionItem(entry.name.c_str(), entry.path.c_str(), entry.hash.c_str()));
		});

	listView->setModel(model);
}
