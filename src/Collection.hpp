#pragma once

#include <string>
#include <vector>

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

	public:
		Collection();
		~Collection();

		void Rebuild();
		void Build();

		void Clean();
		void Scan(std::string path, bool recursive);

		std::vector<CollectionEntry> GetList();
};
