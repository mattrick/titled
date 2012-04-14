#include "MyApplication.hpp"




void MyApplication::collectionSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
	 if (current.isValid())
	 {
		 mainWin->collectionListView->setEnabled(false);
		 filterGroup->setEnabled(false);
		 QString name = collectionModel->data(current, CollectionItem::NameRole).toString();

		 QStringList tokens = name.split(QRegExp("[^\\w']"), QString::SkipEmptyParts);

		 filterGroup->makeList(tokens);

		 mainWin->filmwebWebView->load(QUrl("about:blank"));
		 mainWin->previewEdit->clear();
	 }
}


void MyApplication::queryFinished(bool ok)
{
	mainWin->resultsListView->setCurrentIndex(QModelIndex());

	mainWin->collectionListView->setEnabled(true);
	filterGroup->setEnabled(true);

	if (!ok)
	{
		resultsModel->clear();

		mainWin->resultsListView->setItemDelegate(new InfoDelegate(mainWin->resultsListView));

		resultsModel->appendRow(new InfoItem(tr("Error fetching search results"), tr("query timeout")));
	}
}

/*
 * TODO:
 *
 * Custom saving scheme
 *
 */

void MyApplication::resultsSelectionChanged(const QModelIndex & current, const QModelIndex & previous)
{
	if (current.isValid())
	{
		mainWin->filmwebWebView->load(resultsModel->data(current, ResultsItem::URLRole).toString());

		QString newname = resultsModel->data(current, ResultsItem::TitleRole).toString();
		newname += " (" + resultsModel->data(current, ResultsItem::YearRole).toString() + ")";

		if (!filterGroup->getExtras().empty())
			newname += " " + filterGroup->getExtras().join(".");

		mainWin->previewEdit->setText(newname);
	}
}

void MyApplication::onQueryChange(QStringList words)
{
	filmwebSearch->queryChanged(words);
	resultsModel->clear();

	mainWin->resultsListView->setItemDelegate(new ResultsListViewDelegate(mainWin->resultsListView));
}

void MyApplication::rename()
{
	QString path = collectionModel->data(mainWin->collectionListView->currentIndex(), CollectionItem::PathRole).toString();

	QFile file(path);
	QFileInfo info(file);

	QString newpath = info.absoluteDir().absoluteFilePath(mainWin->previewEdit->text() + "." + info.completeSuffix());

	file.rename(newpath);

	collectionModel->Update();

	clearEverything();
}

void MyApplication::clearEverything()
{
	mainWin->collectionListView->setCurrentIndex(QModelIndex());

	resultsModel->clear();
	mainWin->resultsListView->setCurrentIndex(QModelIndex());

	filterGroup->clear();

	mainWin->filmwebWebView->load(QUrl("about:blank"));

	mainWin->previewEdit->clear();
}

void MyApplication::openSettings()
{
	settingsWidget = new SettingsWidget();
	settingsWidget->show();

	connect(settingsWidget, SIGNAL(settingsChanged()), this, SLOT(onSettingsChanged()));
}

void MyApplication::onSettingsChanged()
{
	collectionModel->Rebuild();

	mainWin->collectionListView->setCurrentIndex(QModelIndex());
}

void MyApplication::onCountChanged(int count)
{
	if (count)
	{
		if (!std::is_same<decltype(mainWin->collectionListView->itemDelegate()), CollectionListViewDelegate>::value)
			mainWin->collectionListView->setItemDelegate(new CollectionListViewDelegate(mainWin->collectionListView));
	}
	else
	{
		mainWin->collectionListView->setItemDelegate(new InfoDelegate(mainWin->collectionListView));
		collectionModel->appendRow(new InfoItem("Your collection is empty!", "visit settings"));
	}
}

void MyApplication::onNoResults()
{
	resultsModel->clear();

	mainWin->resultsListView->setItemDelegate(new InfoDelegate(mainWin->resultsListView));

	resultsModel->appendRow(new InfoItem(tr("No matching titles"), "change your query"));
}
