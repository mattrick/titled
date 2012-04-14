#pragma once

#include <QWidget>
#include <QAbstractItemDelegate>

class QTabWidget;
class QListWidget;
class QLabel;
class QPushButton;

class SettingsWindow : public QWidget
{
	Q_OBJECT

	private:
		QTabWidget *tabWidget;
		QWidget *collectionTab;
		QListWidget *extensionsList;
		QLabel *dirsListLabel;
		QLabel *extensionsListLabel;
		QListWidget *dirsList;
		QPushButton *applyButton;
		QPushButton *deleteDirectoryButton;
		QPushButton *addDirectoryButton;
		QPushButton *addExtensionButton;
		QPushButton *deleteExtensionButton;

		void setupTabWidget();
		void setupCollectionTab();
		void setupConnects();

	public:
		SettingsWindow(QWidget* parent = 0);

	private slots:
		void saveSettings();

		void addDirectory();
		void deleteDirectory();

		void addExtension();
		void deleteExtension();
		void onCloseEditor(QWidget* editor, QAbstractItemDelegate::EndEditHint hint);

	signals:
		void settingsChanged();
};
