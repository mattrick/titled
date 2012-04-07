#include "Collection.hpp"

#include <QSettings>
#include <QCryptographicHash>
#include <QFile>
#include <QDirIterator>
#include <QRegExp>

Collection::Collection()
{
	QSettings settings;

	settings.beginGroup("Collection");
	m_DB = new SQLite3x::DB(settings.value("database", "sqlite.db").toString().toStdString());
	m_Paths = settings.value("paths", QStringList("")).toStringList();
	settings.endGroup();
}

Collection::~Collection()
{
	QSettings settings;

	settings.beginGroup("Collection");
	settings.setValue("database", QString::fromStdString(m_DB->GetFileName()));
	settings.setValue("paths", m_Paths);
	settings.endGroup();

	delete m_DB;
}

void Collection::Update()
{
	try
	{
		m_DB->Exec("CREATE TABLE IF NOT EXISTS movies (name TEXT, path TEXT, hash VARCHAR(32), size INTEGER);");
	}
	catch (std::string err)
	{
		std::cerr << err;
	}
	Check();

	Scan();
}

QString GetHash(QString path)
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

void Collection::Check()
{
	List([m_DB](QString name, QString path, QString hash, qint64 size){
		QFile file(path);
		QFileInfo info(file);

		if (!info.exists())
			m_DB->Query("DELETE FROM movies where hash=?")->Bind(hash.toStdString())->Execute();
		else
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
		}
	});
}

void Collection::Scan()
{
	foreach (QString path, m_Paths)
	{
		QDirIterator directory_walker(path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

		while(directory_walker.hasNext())
		{
			directory_walker.next();

			QRegExp regexp("(3g2|3gp|asf|asx|avi|flv|mov|mp4|mpg|rm|swf|vob|wmv|mkv|rmvb)", Qt::CaseInsensitive);

			if (regexp.exactMatch(directory_walker.fileInfo().completeSuffix()))
			{
				QFileInfo info = directory_walker.fileInfo();

				try
				{
					bool found = false;
					m_DB->Query("SELECT * FROM movies WHERE hash=?;")->Bind(GetHash(info.absoluteFilePath()).toStdString())->Execute([&found](){
					found = true;
					});

					if (!found)
						m_DB->Query("INSERT INTO movies VALUES (?, ?, ?, ?);")->Bind(info.baseName().toUtf8().constData(), info.absoluteFilePath().toUtf8().constData(), GetHash(info.absoluteFilePath()).toStdString(), info.size())->Execute();
				}
				catch(std::string err)
				{
					std::cerr << err;
				}
			}
		}
	}
}

void Collection::List(std::function<void (QString, QString, QString, qint64)> func)
{
	m_DB->Query("SELECT * FROM movies ORDER BY name")->Execute([&func](std::string name, std::string path, std::string hash, int64 size){
		func(QString::fromUtf8(name.c_str()), QString::fromUtf8(path.c_str()), QString::fromUtf8(hash.c_str()), size);
	});
}
