#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>

#include <Poco/DirectoryIterator.h>
#include <Poco/FileStream.h>
#include <Poco/MD5Engine.h>
#include <Poco/DigestStream.h>
#include <Poco/StreamCopier.h>

#include <boost/xpressive/xpressive.hpp>

using Poco::DirectoryIterator;
using Poco::Path;
using Poco::FileInputStream;

using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::DigestOutputStream;
using Poco::StreamCopier;
using Poco::File;

using namespace boost::xpressive;

#include "Collection.hpp"

std::string GetHash(Path path)
{
	MD5Engine md5;

	FileInputStream fis(path.toString(), std::ios::binary);
	DigestOutputStream ostr(md5);

	StreamCopier::copyStream(fis, ostr);
	ostr.close();

	return DigestEngine::digestToHex(md5.digest());
}

Collection::Collection()
{
	m_DB = new SQLite3x::DB("movies.db");
}

Collection::~Collection()
{
	delete m_DB;
}

void Collection::Clean()
{
	m_DB->Query("SELECT * FROM movies")->Execute([m_DB](int id, std::string name, std::string path, std::string hash){
		Path p(path);
		File f(p);

		if (!f.exists())
		{
			m_DB->Query("DELETE FROM movies where id=?")->Bind(id)->Execute();
		}
		else
		{
			if (GetHash(p) != hash)
			{
				try
				{
					m_DB->Query("UPDATE movies SET hash=? WHERE id=?")->Bind(GetHash(p), id)->Execute();
				}
				catch (const char* err)
				{
					std::cout << err;
				}
			}
		}
	});
}

void Collection::Rebuild()
{
	//truncate isn't available in sqlite, so we force delete table
	m_DB->Exec("DROP TABLE IF EXISTS movie");
	Build();
}

void Collection::Build()
{
	m_DB->Exec("CREATE TABLE IF NOT EXISTS %s (%s INTEGER PRIMARY KEY, %s TEXT, %s TEXT, %s VARCHAR(32));", "movies", "id", "name", "path", "hash");

	std::string dir = std::string(Path::current());

	Clean();

	Scan(dir, true);
}

void Collection::Scan(std::string path, bool recursive = true)
{
	DirectoryIterator it(path);
	DirectoryIterator end;

	while (it != end)
	{
		sregex extension_check = sregex::compile("(mp4|avi|rmvb|rm|256)");
		if (it->isFile() && regex_match(it.path().getExtension(), extension_check))
		{
			bool found = false;

			try
			{
			m_DB->Query("SELECT * FROM movies WHERE hash=?;")->Bind(GetHash(it.path()).c_str())->Execute([&found](int id){
				found = true;
			});

			if (!found)
			{
				m_DB->Query("INSERT INTO movies VALUES (null, ?, ?, ?);")->Bind(it.path().getBaseName(), it.path().toString(), GetHash(it.path()))->Execute();
			}

			}
			catch(const char* err)
			{
				std::cerr << err;
			}
		}

		if (it->isDirectory() && recursive)
		{
			Scan(it.path().toString(), true);
		}

		++it;
	}
}
