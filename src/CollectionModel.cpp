#include "Collection.hpp"
#include "CollectionModel.hpp"
#include "CollectionItem.hpp"

#include <QSettings>

CollectionModel::CollectionModel(QObject *parent)
	: MyListModel(parent)
{
	m_Collection = new Collection();
}

CollectionModel::~CollectionModel()
{
	delete m_Collection;
}

void CollectionModel::Update()
{
	m_Collection->Update();

	clear();

	m_Collection->List([this](QString name, QString path, QString hash, qint64 size, bool subdir){
		this->appendRow(new CollectionItem(name, path, hash, size, subdir));
	});

	emit countChanged(rowCount());
}

void CollectionModel::Rebuild()
{
	m_Collection->Rebuild();

	Update();
}
