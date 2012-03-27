#pragma once

#include <string>
#include <list>

#include <Poco/Path.h>

#include <sqlite3x/SQLite3x.hpp>

namespace SQLite3x
{
	class DB;
}

struct CollectionEntry
{
	std::string name;
	std::string path;
	std::string hash;
};

class Collection
{
	private:

	protected:
		SQLite3x::DB *m_DB;
		std::string m_Path;

	public:
		Collection(std::string path = Poco::Path::current());
		~Collection();

		void Rebuild();
		void Build();

		void Clean();
		void Scan(std::string path, bool recursive);

		std::list<CollectionEntry> GetList();
};
