#include <QSettings>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>
#include <QFileDialog>

#include "SettingsWindow.hpp"
#include "Defaults.hpp"

SettingsWindow::SettingsWindow(QWidget* parent)
	: QWidget(parent)
{
	if (objectName().isEmpty())
		setObjectName(QString::fromUtf8("settingsWindow"));
	resize(640, 480);
	setWindowTitle(tr("Settings"));

	setupTabWidget();
	setupCollectionTab();
	setupConnects();
}

void SettingsWindow::setupTabWidget()
{
	tabWidget = new QTabWidget(this);
	tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
	tabWidget->setGeometry(QRect(0, 0, 640, 480));


	collectionTab = new QWidget();
	collectionTab->setObjectName(QString::fromUtf8("collectionTab"));

	tabWidget->addTab(collectionTab, tr("Collection"));

	tabWidget->setCurrentIndex(0);
}

void SettingsWindow::setupCollectionTab()
{
	QSettings settings;

	settings.beginGroup("Collection");
	QStringList paths = settings.value("paths", Default::paths).toStringList();
	QStringList extensions = settings.value("extensions", Default::extensions).toStringList();
	settings.endGroup();

	dirsListLabel = new QLabel(collectionTab);
	dirsListLabel->setObjectName(QString::fromUtf8("dirsListLabel"));
	dirsListLabel->setGeometry(QRect(30, 10, 191, 16));
	dirsListLabel->setText(tr("Scan following directories:"));

	dirsList = new QListWidget(collectionTab);
	dirsList->setObjectName(QString::fromUtf8("dirsList"));
	dirsList->setGeometry(QRect(30, 30, 311, 192));
	foreach (QString s, paths)
	{
		if (!s.isEmpty())
		{
			QListWidgetItem *item = new QListWidgetItem(s, dirsList);
			item->setFlags(item->flags() | Qt::ItemIsEditable);
		}
	}

	addDirectoryButton = new QPushButton(collectionTab);
	addDirectoryButton->setObjectName(QString::fromUtf8("addDirectoryButton"));
	addDirectoryButton->setGeometry(QRect(160, 230, 91, 24));
	addDirectoryButton->setText(tr("Add directory"));

	deleteDirectoryButton = new QPushButton(collectionTab);
	deleteDirectoryButton->setObjectName(QString::fromUtf8("deleteButton"));
	deleteDirectoryButton->setGeometry(QRect(260, 230, 83, 24));
	deleteDirectoryButton->setText(tr("Delete"));

	extensionsListLabel = new QLabel(collectionTab);
	extensionsListLabel->setObjectName(QString::fromUtf8("extensionsListLabel"));
	extensionsListLabel->setGeometry(QRect(370, 10, 201, 16));
	extensionsListLabel->setText(tr("Scan for following extensions:"));

	extensionsList = new QListWidget(collectionTab);
	extensionsList->setObjectName(QString::fromUtf8("extensionsList"));
	extensionsList->setGeometry(QRect(369, 30, 191, 191));
	foreach (QString s, extensions)
	{
		if (!s.isEmpty())
		{
			QListWidgetItem *item = new QListWidgetItem(s, extensionsList);
			item->setFlags(item->flags() | Qt::ItemIsEditable);
		}
	}

	addExtensionButton = new QPushButton(collectionTab);
  addExtensionButton->setObjectName(QString::fromUtf8("addExtensionButton"));
  addExtensionButton->setGeometry(QRect(390, 230, 83, 24));
  addExtensionButton->setText(tr("Add"));


  deleteExtensionButton = new QPushButton(collectionTab);
  deleteExtensionButton->setObjectName(QString::fromUtf8("deleteExtensionButton"));
  deleteExtensionButton->setGeometry(QRect(480, 230, 83, 24));
  deleteExtensionButton->setText(tr("Delete"));


	applyButton = new QPushButton(collectionTab);
	applyButton->setObjectName(QString::fromUtf8("applyButton"));
	applyButton->setGeometry(QRect(540, 420, 83, 24));
	applyButton->setText(tr("Apply"));
}

void SettingsWindow::setupConnects()
{
	connect(applyButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

	connect(addDirectoryButton, SIGNAL(clicked()), this, SLOT(addDirectory()));
	connect(deleteDirectoryButton, SIGNAL(clicked()), this, SLOT(deleteDirectory()));

	connect(addExtensionButton, SIGNAL(clicked()), this, SLOT(addExtension()));
	connect(deleteExtensionButton, SIGNAL(clicked()), this, SLOT(deleteExtension()));
}

void SettingsWindow::saveSettings()
{
	QStringList paths;

	for (int i = 0; i < dirsList->count(); i++)
	{
		paths << dirsList->item(i)->text();
	}

	QStringList extensions;

	for (int i = 0; i < extensionsList->count(); i++)
	{
		extensions << extensionsList->item(i)->text();
	}

	QSettings settings;

	settings.beginGroup("Collection");
	settings.setValue("paths", paths);
	settings.setValue("extensions", extensions);
	settings.endGroup();

	emit settingsChanged();
}

void SettingsWindow::addDirectory()
{
	QStringList dirs;

	QFileDialog dialog;
	dialog.setFileMode(QFileDialog::Directory);
	dialog.setOption(QFileDialog::ShowDirsOnly, true);

	if (dialog.exec())
		dirs = dialog.selectedFiles();

	foreach (QString dir, dirs)
	{
		if (!dir.isEmpty())
		{
			QListWidgetItem* item = new QListWidgetItem(dir, dirsList);
			item->setFlags(item->flags() | Qt::ItemIsEditable);
		}
	}
}

void SettingsWindow::deleteDirectory()
{
	if (dirsList->currentIndex().isValid())
	{
		dirsList->takeItem(dirsList->currentRow());
	}
}

void SettingsWindow::addExtension()
{

	QListWidgetItem* item = new QListWidgetItem("", extensionsList);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	extensionsList->setCurrentItem(item);
	extensionsList->editItem(item);

	connect(extensionsList->itemDelegate(), SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)), this, SLOT(onCloseEditor(QWidget*, QAbstractItemDelegate::EndEditHint)));
}

void SettingsWindow::deleteExtension()
{
	if (extensionsList->currentIndex().isValid())
	{
		extensionsList->takeItem(extensionsList->currentRow());
	}
}

void SettingsWindow::onCloseEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint)
{
	if (extensionsList->currentItem()->text().isEmpty())
		deleteExtension();
}
