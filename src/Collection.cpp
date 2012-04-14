#include <iostream>

#include <QSettings>
#include <QCryptographicHash>
#include <QFile>
#include <QDirIterator>
#include <QRegExp>

#include <sqlite3x/SQLite3x.hpp>

#include "Defaults.hpp"
#include "Collection.hpp"

QString GetHash(const QString& path)
{
	QCryptographicHash crypto(QCryptographicHash::Md5);

	QFile file(path);
	file.open(QFile::ReadOnly);

	while (!file.atEnd())
	{
		crypto.addData(file.read(8192));
	}

	return QString(crypto.result().toHex());
}


Collection::Collection()
{
	m_DB = new SQLite3x::DB("sqlite.db");
}

Collection::~Collection()
{
	delete m_DB;
}

void Collection::Update()
{
	try
	{
		m_DB->Exec("CREATE TABLE IF NOT EXISTS movies (name TEXT, path TEXT, hash VARCHAR(32), size INTEGER, subdir BOOLEAN);");
	}
	catch (std::string err)
	{
		std::cerr << err;
	}

	Clean();

	Scan();
}

void Collection::Clean()
{
	List([this](QString name, QString path, QString hash, qint64 size, bool subdir){
		QFile file(path);
		QFileInfo info(file);

		if (!info.exists() || QSettings().value("Collection/extensions", Default::extensions).toStringList().contains(info.completeSuffix()))
			m_DB->Query("DELETE FROM movies where hash=?")->Bind(hash.toStdString())->Execute();
	});
}

void Collection::Rebuild()
{
	m_DB->Exec("DELETE FROM movies");

	Scan();
}

void Collection::Scan()
{
	foreach (QString path, QSettings().value("Collection/paths", Default::paths).toStringList())
	{
		/*
		 * FIXME:
		 *
		 * Files are scanned twice cause of "." directory in each subdir
		 *
		 */

		QDirIterator directories(path, QDir::Dirs | QDir::NoDotDot, QDirIterator::Subdirectories);

		while(directories.hasNext())
		{
			QStringList extensions = QSettings().value("Collection/extensions", Default::extensions).toStringList();

			extensions.replaceInStrings(QRegExp("^(.*)$"), "*.\\1");

			QStringList files = QDir(directories.next()).entryList(extensions, QDir::Files);

			bool aloneInSubdir = true;

			if (files.size() > 1)
				aloneInSubdir = false;

		/*
		 * TODO:
		 *
		 * Checking for changes in hash/size/another files in subdir presence.
		 *
		 */

			/*else
					{
						if (GetHash(path) != hash)
						{
							try
							{
								m_DB->Query("UPDATE movies SET size=? WHERE hash=?")->Bind(info.size(), hash.toStdString())->Execute();
								m_DB->Query("UPDATE movies SET hash=? WHERE hash=?")->Bind(GetHash(path).toUtf8().constData(), hash.toStdString())->Execute();
							}
							catch (std::string err)
							{
								std::cout << err;
							}
						}
					}*/
			foreach (QString file, files)
			{
				QFileInfo info(directories.filePath() + "/" + file);

				try
				{
					bool found = false;
					m_DB->Query("SELECT * FROM movies WHERE hash=?;")->Bind(GetHash(info.absoluteFilePath()).toStdString())->Execute([&found](){
						found = true;
					});

					if (!found)
						m_DB->Query("INSERT INTO movies VALUES (?, ?, ?, ?, ?);")->Bind(info.baseName().toUtf8().constData(), info.absoluteFilePath().toUtf8().constData(), GetHash(info.absoluteFilePath()).toStdString(), info.size(), aloneInSubdir)->Execute();
				}
				catch(std::string err)
				{
					std::cerr << err;
				}
			}
		}
	}
}

void Collection::List(std::function<void (const QString&, const QString&, const QString&, qint64, bool)> func)
{
	m_DB->Query("SELECT * FROM movies ORDER BY name")->Execute([&func](std::string name, std::string path, std::string hash, int64 size, bool subdir){
		func(QString::fromUtf8(name.c_str()), QString::fromUtf8(path.c_str()), QString::fromUtf8(hash.c_str()), size, subdir);
	});
}
