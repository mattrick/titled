#pragma once

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QSettings>
#include <QFileDialog>
#include <QDebug>

class SettingsWidget : public QWidget
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
	SettingsWidget(QWidget* parent = 0);

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
