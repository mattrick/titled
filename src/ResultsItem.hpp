#pragma once

#include <QStandardItem>
#include <QObject>
#include <QHash>
#include <QVariant>

class ResultsItem : public QStandardItem
{
	public:
		enum Roles {
			  TitleRole = Qt::UserRole+1,
			  OriginalRole,
			  YearRole,
			  URLRole
			};

		 ResultsItem(QObject *parent = 0);
		 ResultsItem(const QString &title, const QString &original, const QString &year, const QString &url, QObject *parent = 0);
	    QVariant data(int role) const;

	private:
		QString m_Title;
		QString m_Original;
		QString m_Year;
		QString m_URL;
};
