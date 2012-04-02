#pragma once

#include <QObject>
#include <QHash>
#include <QVariant>

class ResultsItem : public QObject
{
	Q_OBJECT

public:
	enum Roles {
	      TitleRole = Qt::UserRole+1,
	      OriginalRole,
	      YearRole
	    };

	 ResultsItem(QObject *parent = 0);
	    explicit ResultsItem(const QString &title, const QString &original, const QString &year, QObject *parent = 0);
	    QVariant data(int role) const;

	    QHash<int, QByteArray> roleNames() const;

	private:
		QString m_Title;
		QString m_Original;
		QString m_Year;

};
