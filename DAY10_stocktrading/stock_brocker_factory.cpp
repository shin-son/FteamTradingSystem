#include "stock_brocker_factory.h"

StockBrokerDriverInterface* stockBrockerFactory::getInstance(const string& brockerName)
{
	if ("키워" == brockerName)
	{
		return new KiwerDriver();
	}
	else if ("네모" == brockerName)
	{
		return new NemoDriver();
	}
	else
	{
		throw std::invalid_argument("stock brocker name is invalid!");
	}
}