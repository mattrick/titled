#pragma once

#include <functional>

#include <QtGlobal>

class QString;
class QStringList;

namespace SQLite3x
{
	class DB;
}

class Collection
{
	private:

	protected:
		SQLite3x::DB* m_DB;

		void Clean();
		void Scan();

	public:
		Collection();
		~Collection();

		void Update();
		void Rebuild();
		void List(std::function<void (const QString&, const QString&, const QString&, qint64, bool)> func);
};
