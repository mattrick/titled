#include "WordDB.hpp"

WordDB::WordDB()
{
	m_DB = new SQLite3x::DB("sqlite.db");

	m_DB->Exec("CREATE TABLE IF NOT EXISTS words (word TEXT, type INTEGER);");
}

WordDB::~WordDB()
{
	delete m_DB;
}

void WordDB::List(std::string word, WordDB::Type type)
{
	if (Check(word) != type)
	{
		if (!Check(word))
			m_DB->Query("INSERT INTO words VALUES (?, ?);")->Bind(word, (int)type)->Execute();
		else
			m_DB->Query("UPDATE words SET type=? WHERE word=?);")->Bind((int)type, word)->Execute();
	}
}

void WordDB::Remove(std::string word)
{
	if (Check(word))
		m_DB->Query("DELETE FROM words WHERE word=?")->Bind(word)->Execute();
}

WordDB::Type WordDB::Check(std::string word)
{
	WordDB::Type type = None;

	m_DB->Query("SELECT type FROM words WHERE word=?")->Bind(word)->Execute([&type](int _type){
		type = (WordDB::Type)_type;
	});

	return type;
}
