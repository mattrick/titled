#include "Filter.hpp"
#include "FilterGroup.hpp"

#include <QDebug>

Filter::Filter(QString text, int x, int y, QWidget * parent, Qt::WindowFlags f)
	: QWidget(parent, f)
{
	m_lineEdit = new QLineEdit(this);
	m_lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
	m_lineEdit->setText(text);

	m_horizontalLayoutWidget = new QWidget(this);

	m_horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));

	m_horizontalLayout = new QHBoxLayout(m_horizontalLayoutWidget);
	m_horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	m_horizontalLayout->setContentsMargins(0, 0, 0, 0);

	m_add = new QPushButton(m_horizontalLayoutWidget);
	m_add->setFlat(true);
	m_add->setObjectName(QString::fromUtf8("add"));
	m_add->setText("+");
	m_horizontalLayout->addWidget(m_add);

	m_horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_horizontalLayout->addItem(m_horizontalSpacer);

	m_remove = new QPushButton(m_horizontalLayoutWidget);
	m_remove->setFlat(true);
	m_remove->setObjectName(QString::fromUtf8("remove"));
	m_remove->setText("-");
	m_horizontalLayout->addWidget(m_remove);

	m_horizontalSpacer2 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_horizontalLayout->addItem(m_horizontalSpacer2);

	m_include = new QPushButton(m_horizontalLayoutWidget);
	m_include->setFlat(true);
	m_include->setObjectName(QString::fromUtf8("include"));
	m_include->setText("*");
	m_horizontalLayout->addWidget(m_include);

	m_horizontalSpacer3 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_horizontalLayout->addItem(m_horizontalSpacer3);

	m_exclude = new QPushButton(m_horizontalLayoutWidget);
	m_exclude->setFlat(true);
	m_exclude->setObjectName(QString::fromUtf8("exclude"));
	m_exclude->setText("x");
	m_horizontalLayout->addWidget(m_exclude);

	m_horizontalSpacer4 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
	m_horizontalLayout->addItem(m_horizontalSpacer4);

	m_search = new QPushButton(m_horizontalLayoutWidget);
	m_search->setFlat(true);
	m_search->setObjectName(QString::fromUtf8("search"));
	m_search->setText("?");
	m_horizontalLayout->addWidget(m_search);

	int lineEdit_width = m_lineEdit->fontMetrics().width(m_lineEdit->text()) + 10;
	int horizontalLayout_width = m_add->fontMetrics().width("+") + m_remove->fontMetrics().width("-") + m_include->fontMetrics().width("*") + m_exclude->fontMetrics().width("x") + m_search->fontMetrics().width("?") + 44;

	int width = std::max(lineEdit_width, horizontalLayout_width);

	m_lineEdit->setGeometry(0, 0, width, 20);

	int height = m_lineEdit->height();

	m_add->setGeometry(0, 0, m_add->fontMetrics().width("+") + 20, m_add->fontMetrics().height());
	m_remove->setGeometry(0, 0, m_remove->fontMetrics().width("-") + 20, m_remove->fontMetrics().height());
	m_include->setGeometry(0, 0, m_include->fontMetrics().width("*") + 20, m_include->fontMetrics().height());
	m_exclude->setGeometry(0, 0, m_exclude->fontMetrics().width("x") + 20, m_exclude->fontMetrics().height());
	m_search->setGeometry(0, 0, m_search->fontMetrics().width("?") + 20, m_search->fontMetrics().height());

	m_horizontalLayoutWidget->setGeometry(QRect(0, 0 + height, width, height));
	setGeometry(QRect(x, y, width, 2 * height));

	FilterGroup* fg = (FilterGroup *) parent;

	connect(m_add, SIGNAL(clicked(bool)), this, SLOT(update()));
	connect(m_remove, SIGNAL(clicked(bool)), this, SLOT(update()));
	connect(m_include, SIGNAL(clicked(bool)), this, SLOT(update()));
	connect(m_exclude, SIGNAL(clicked(bool)), this, SLOT(update()));
	connect(m_search, SIGNAL(clicked(bool)), this, SLOT(update()));

	connect(this, SIGNAL(changed(Action, QString)), fg, SLOT(update(Action, QString)));
}

void Filter::update()
{
	if (sender()->objectName() == m_add->objectName())
		emit changed(Action::ADD, m_lineEdit->text());

	if (sender()->objectName() == m_remove->objectName())
			emit changed(Action::REMOVE, m_lineEdit->text());

	if (sender()->objectName() == m_include->objectName())
			emit changed(Action::INCLUDE, m_lineEdit->text());

	if (sender()->objectName() == m_exclude->objectName())
			emit changed(Action::EXCLUDE, m_lineEdit->text());

	if (sender()->objectName() == m_search->objectName())
			emit changed(Action::SEARCH, m_lineEdit->text());
}
