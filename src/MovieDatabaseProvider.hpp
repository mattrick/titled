#pragma once

#include <QObject>

class ResultsModel;
class QStringList;

class MovieDatabaseProvider : public QObject
{
	Q_OBJECT

	private:

	protected:
		ResultsModel* m_ResultsModel;

	public:
		MovieDatabaseProvider(ResultsModel* resultsModel, QObject* parent = 0)
			: m_ResultsModel(resultsModel), QObject(parent)
		{
		}

		virtual void query(const QStringList& words) = 0;

	signals:
		void queryStarted();
		void queryFinished(int);
		void queryTimeout();
};
