#pragma once

#include <functional>

#include <QStringList>
#include <QString>

#include <sqlite3x/SQLite3x.hpp>

class Collection
{
	private:

	protected:
		SQLite3x::DB *m_DB;
		QStringList m_Paths;

		void Check();
		void Scan();

	public:
		Collection();
		~Collection();

		void Update();
		void List(std::function<void (QString, QString, QString)> func);
};
