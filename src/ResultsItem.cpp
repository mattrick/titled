#include "ResultsItem.hpp"

ResultsItem::ResultsItem(QObject *parent)
{
}

ResultsItem::ResultsItem(const QString &title, const QString &original, const QString &original, QObject *parent)
	: m_Title(title), m_Original(original), m_Year(year)
{
}

QHash<int, QByteArray> ResultsItem::roleNames() const
{
  QHash<int, QByteArray> names;
  names[TitleRole] = "title";
  names[OriginalRole] = "original";
  names[YearRole] = "year";
  return names;
}

QVariant ResultsItem::data(int role) const
{
  switch(role) {
  case Qt::DisplayRole:
    return m_Title;
  case TitleRole:
    return m_Title;
  case OriginalRole:
    return m_Original;
  case YearRole:
    return m_Year;
  default:
    return QVariant();
  }
}
