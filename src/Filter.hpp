#pragma once

#include <QWidget>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QHBoxLayout>

 class Filter : public QWidget
 {
	 Q_OBJECT

 public:
	 enum Action
	 {
		 ADD = 100,
		 REMOVE,
		 INCLUDE,
		 EXCLUDE,
		 SEARCH
	 };

 private:
	 QPushButton* m_add;
	 QPushButton* m_remove;
	 QPushButton* m_include;
	 QPushButton* m_exclude;
	 QPushButton* m_search;

	 QSpacerItem* m_horizontalSpacer;
	 QSpacerItem* m_horizontalSpacer2;
	 QSpacerItem* m_horizontalSpacer3;
	 QSpacerItem* m_horizontalSpacer4;

	 QWidget* m_horizontalLayoutWidget;
	 QHBoxLayout* m_horizontalLayout;

	 QLineEdit* m_lineEdit;

signals:
	void changed(Action type, QString text);

private slots:
	void update();

public:
	 explicit Filter(QString text, int x, int y, QWidget * parent = 0, Qt::WindowFlags f = 0);

	 const QString& text() const;
 };
