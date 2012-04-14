#pragma once

#include <QStandardItem>

QString FormatSizeInBytes(qint64 bytes);

class CollectionItem : public QStandardItem
{
	private:
		QString m_Name;
		QString m_Path;
		QString m_Hash;
		qint64 m_Size;
		bool m_Subdir;

	public:
		enum Roles
		{
			NameRole = Qt::UserRole,
			PathRole,
			HashRole,
			SizeRole,
			SizeTextRole,
			SubdirRole,
			SubdirTextRole
		};

		CollectionItem();
	    explicit CollectionItem(const QString& name, const QString& path, const QString& hash, qint64 size, bool subdir);
	    QVariant data(int role) const;

	    inline QString name() const { return m_Name; }
	    inline QString path() const { return m_Path; }
	    inline QString hash() const { return m_Hash; }
	    inline qint64 size() const { return m_Size; }
	    inline QString sizeText() const { return FormatSizeInBytes(m_Size); }
	    inline bool subdir() const { return m_Subdir; }
	    inline QString subdirText() const { return ((m_Subdir) ? ("yes") : ("no")); }
};
