#pragma once

#include "MyListModel.hpp"
#include "CollectionItem.hpp"
#include <QStringList>

class Collection;

class CollectionModel : public MyListModel
{
	Q_OBJECT

	private:

		Collection *m_Collection;

		void UpdateList();

	protected:

	public:
		CollectionModel(QObject* parent);
		~CollectionModel();

	public slots:
		void Update();
		void Rebuild();

	signals:
		void countChanged(int);
};

