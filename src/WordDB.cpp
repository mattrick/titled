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

void WordDB::List(QString word, WordDB::Type type)
{
	if (Check(word) != type && type != WordDB::None)
	{
		if (!Check(word))
			m_DB->Query("INSERT INTO words VALUES (?, ?);")->Bind(word.toUtf8().constData(), (int)type)->Execute();
		else
			m_DB->Query("UPDATE words SET type=? WHERE word=?);")->Bind((int)type, word.toUtf8().constData())->Execute();
	}
}

void WordDB::Remove(QString word)
{
	if (Check(word))
		m_DB->Query("DELETE FROM words WHERE word=?")->Bind(word.toUtf8().constData())->Execute();
}

WordDB::Type WordDB::Check(QString word)
{
	WordDB::Type type = None;

	m_DB->Query("SELECT type FROM words WHERE word=?")->Bind(word.toUtf8().constData())->Execute([&type](int _type){
		type = (WordDB::Type)_type;
	});

	return type;
}
