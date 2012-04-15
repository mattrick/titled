#pragma once

#include <QObject>
#include <QStringList>

#include "ResultsModel.hpp"
#include "ResultsItem.hpp"

class Provider : public QObject
{
	Q_OBJECT

	private:

	protected:

	public:
		virtual ~Provider() {}
		Provider() {};

	public slots:
		virtual void query(const QStringList& tokens) = 0;

	signals:
		void queryStarted();
		void queryFinished(int);
		void queryTimeout();

	public:
		virtual QString name() const = 0;
};

class ProviderFactory
{
	private:

	protected:

	public:
		virtual Provider* GetProvider(ResultsModel* model, QObject* parent = 0) = 0;
};

 Q_DECLARE_INTERFACE(ProviderFactory, "titled.Plugin.ProviderFactory/1.0");
