#pragma once

#include <QStandardItem>

class InfoItem : public QStandardItem
{
	private:

	protected:

	public:
		enum Role
		{
			InfoHeaderRole = 123456,
			InfoSubRole
		};

		InfoItem(QString header, QString sub, QObject* parent = 0);
};
