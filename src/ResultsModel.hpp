#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QStringList>
#include <QStandardItem>
#include "MyListModel.hpp"

class ResultsItem;
class FilmwebSearch;

class ResultsModel : public MyListModel
{
	Q_OBJECT

	public:
		ResultsModel(QObject *parent = 0);
		~ResultsModel();

	signals:
		void countChanged(int);
};

