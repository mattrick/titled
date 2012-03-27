#pragma once

#include <QObject>
#include <QHash>
#include <QVariant>

class CollectionItem : public QObject
{
	Q_OBJECT

public:
	enum Roles {
	      NameRole = Qt::UserRole+1,
	      PathRole,
	      HashRole
	    };

	 CollectionItem(QObject *parent = 0);
	    explicit CollectionItem(const QString &name, const QString &path, const QString &hash, QObject *parent = 0);
	    QVariant data(int role) const;

	    QHash<int, QByteArray> roleNames() const;

	    inline QString name() const { return m_Name; }
	    inline QString path() const { return m_Path; }
	    inline QString hash() const { return m_Hash; }

	private:
		QString m_Name;
		QString m_Path;
		QString m_Hash;

};
