#pragma once

#include <QObject>
#include <QHash>
#include <QVariant>

QString FormatSizeInBytes(qint64 bytes);

class CollectionItem : public QObject
{
	Q_OBJECT

public:
	enum Roles {
	      NameRole = Qt::UserRole+1,
	      PathRole,
	      HashRole,
	      SizeRole,
	      SizeTextRole,
	      SubdirRole,
	      SubdirTextRole
	    };

	 CollectionItem(QObject *parent = 0);
	    explicit CollectionItem(const QString &name, const QString &path, const QString &hash, qint64 &size, bool subdir, QObject *parent = 0);
	    QVariant data(int role) const;

	    QHash<int, QByteArray> roleNames() const;

	    inline QString name() const { return m_Name; }
	    inline QString path() const { return m_Path; }
	    inline QString hash() const { return m_Hash; }
	    inline qint64 size() const { return m_Size; }
	    inline QString sizeText() const { return FormatSizeInBytes(m_Size); }
	    inline bool subdir() const { return m_Subdir; }
	    inline QString subdirText() const { return ((m_Subdir) ? ("yes") : ("no")); }

	private:
		QString m_Name;
		QString m_Path;
		QString m_Hash;
		qint64 m_Size;
		bool m_Subdir;
};
