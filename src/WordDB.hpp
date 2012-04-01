#pragma once

#include <sqlite3x/SQLite3x.hpp>

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
	void List(std::string word, Type type);
	void Remove(std::string word);
	Type Check(std::string word);

	WordDB();
	~WordDB();
};
