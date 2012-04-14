#pragma once

#include <QStandardItem>

class ResultsItem : public QStandardItem
{
	private:
		QString m_Title;
		QString m_Original;
		QString m_Year;
		QString m_URL;

	protected:

	public:
		enum Roles
		{
			TitleRole = Qt::UserRole,
			OriginalRole,
			YearRole,
			URLRole
		};

		ResultsItem(QObject* parent = 0);
		ResultsItem(const QString& title, const QString& original, const QString& year, const QString& url, QObject* parent = 0);
		QVariant data(int role) const;
};
