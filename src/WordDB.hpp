#pragma once

#include <sqlite3x/SQLite3x.hpp>

#include <QString>

class WordDB
{
protected:
	SQLite3x::DB *m_DB;
public:
	enum Type
	{
		None = 0,
		Black,
		White
	};
	void List(QString word, Type type);
	void Remove(QString word);
	Type Check(QString word);

	WordDB();
	~WordDB();
};
