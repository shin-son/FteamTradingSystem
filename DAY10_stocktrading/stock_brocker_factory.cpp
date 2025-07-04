#include "stock_brocker_factory.h"

StockBrokerDriverInterface* stockBrockerFactory::getInstance(const string& brockerName)
{
	if ("Ű��" == brockerName)
	{
		return new KiwerDriver();
	}
	else if ("�׸�" == brockerName)
	{
		return new NemoDriver();
	}
	else
	{
		throw std::invalid_argument("stock brocker name is invalid!");
	}
}