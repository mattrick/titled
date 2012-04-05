#include "Collection.hpp"

#include <QSettings>
#include <QCryptographicHash>
#include <QFile>
#include <QDirIterator>

#include <boost/xpressive/xpressive.hpp>
using namespace boost::xpressive;


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
	m_DB->Exec("CREATE TABLE IF NOT EXISTS %s (%s TEXT, %s TEXT, %s VARCHAR(32));", "movies", "name", "path", "hash");

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
	List([m_DB](QString name, QString path, QString hash){
		QFile file(path);
		QFileInfo info(file);

		if (!info.exists())
		{
			m_DB->Query("DELETE FROM movies where hash=?")->Bind(hash.toStdString())->Execute();
		}
		else
		{
			if (GetHash(path) != hash)
			{
				try
				{
					m_DB->Query("UPDATE movies SET hash=? WHERE hash=?")->Bind(GetHash(path).toUtf8().constData(), hash.toStdString())->Execute();
				}
				catch (const char* err)
				{
					std::cout << err;
				}
			}
		}
	});
}

void Collection::Scan()
{
	QSettings settings;
	foreach (QString path, m_Paths)
	{
		QDirIterator directory_walker(path, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

		while(directory_walker.hasNext())
		{
			  // then we tell our directory_walker object to explicitly take next element until the loop finishes
			  directory_walker.next();

			  sregex extension_check = sregex::compile("(3g2|3gp|asf|asx|avi|flv|mov|mp4|mpg|rm|swf|vob|wmv|mkv|rmvb)");
			 // I want to list just mp3 files!
			 if(regex_match(directory_walker.fileInfo().completeSuffix().toStdString(), extension_check))
			 {		 // then we take a filename and display it to a listWidget like the code below:

				 QFileInfo info = directory_walker.fileInfo();

				 try
					{
					 	 bool found = false;
						m_DB->Query("SELECT * FROM movies WHERE hash=?;")->Bind(GetHash(info.absoluteFilePath()).toStdString())->Execute([&found](){
							found = true;
						});

						if (!found)
						{
							m_DB->Query("INSERT INTO movies VALUES (?, ?, ?);")->Bind(info.baseName().toUtf8().constData(), info.absoluteFilePath().toUtf8().constData(), GetHash(info.absoluteFilePath()).toStdString())->Execute();
						}
					}
					catch(const char* err)
					{
						std::cerr << err;
					}
			 }
		}
	}
}

void Collection::List(std::function<void (QString, QString, QString)> func)
{
	m_DB->Query("SELECT * FROM movies ORDER BY name")->Execute([&func](std::string name, std::string path, std::string hash){
		func(QString::fromUtf8(name.c_str()), QString::fromUtf8(path.c_str()), QString::fromUtf8(hash.c_str()));
	});
}
