#include "InfoItem.hpp"

InfoItem::InfoItem(QString header, QString sub, QObject* parent)
{
	QStandardItem::setData(header, InfoItem::InfoHeaderRole);
	QStandardItem::setData(sub, InfoItem::InfoSubRole);

	QStandardItem::setFlags(Qt::NoItemFlags);
}
