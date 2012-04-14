#pragma once

#include "MyListModel.hpp"

class ResultsModel : public MyListModel
{
	Q_OBJECT

	public:
		ResultsModel(QObject *parent = 0);
		~ResultsModel();

	signals:
		void countChanged(int);
};

