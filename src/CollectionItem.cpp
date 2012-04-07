#include "CollectionItem.hpp"

QString FormatSizeInBytes(qint64 bytes)
{
	qint64 B = Q_INT64_C(1);
	qint64 KB = 1024 * B;
	qint64 MB = 1024 * KB;
	qint64 GB = 1024 * MB;
	qint64 TB = 1024 * GB;

	qint64 unit;
	QString unitText;

	if (bytes > TB)
	{
		unit = TB;
		unitText = "TB";
	}
	else if (bytes > GB)
	{
		unit = GB;
		unitText = "GB";
	}
	else if (bytes > MB)
	{
		unit = MB;
		unitText = "MB";
	}
	else if (bytes > KB)
	{
		unit = KB;
		unitText = "KB";
	}
	else
	{
		unit = B;
		unitText = "B";
	}

	double size = (double)bytes / unit;

	int precision = 0;
	if (size - (int)(size) > 0.0)
		precision = 2;

	return QString().setNum(size, 'f', precision) + " " + unitText;
}

CollectionItem::CollectionItem(QObject *parent)
{
}

CollectionItem::CollectionItem(const QString &name, const QString &path, const QString &hash, qint64 &size, QObject *parent)
	: m_Name(name), m_Path(path), m_Hash(hash), m_Size(size)
{
}

QHash<int, QByteArray> CollectionItem::roleNames() const
{
	QHash<int, QByteArray> names;

	names[NameRole] = "name";
	names[PathRole] = "path";
	names[HashRole] = "hash";
	names[SizeRole] = "size";
	names[SizeTextRole] = "sizeText";

	return names;
}

QVariant CollectionItem::data(int role) const
{
	switch(role)
	{
		case Qt::DisplayRole:
			return name();

		case NameRole:
			return name();

		case PathRole:
			return path();

		case HashRole:
			return hash();

		case SizeRole:
			return size();

		case SizeTextRole:
			return sizeText();

		default:
			return QVariant();
	}
}
