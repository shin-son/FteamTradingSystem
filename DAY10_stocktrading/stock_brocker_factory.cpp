#include "stock_brocker_factory.h"

std::unique_ptr<StockBrokerDriverInterface> stockBrockerFactory::getInstance(const string& brockerName)
{
	if ("키워" == brockerName)
	{
		return std::make_unique<KiwerDriver>();
	}
	else if ("네모" == brockerName)
	{
		return std::make_unique<NemoDriver>();
	}
	else
	{
		throw std::invalid_argument("stock brocker name is invalid!");
	}
}