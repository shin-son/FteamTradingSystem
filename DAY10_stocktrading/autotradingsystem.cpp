#pragma once
#include "autotradingsystem.h"

void AutoTradingSystem::selectStockBrocker(const string& brockerName)
{
	brockerDriver = stockBrockerFactory::getInstance(brockerName);
}

void AutoTradingSystem::selectStockBrocker(StockBrokerDriverInterface* new_broker)
{
	brockerDriver = new_broker;
}

bool AutoTradingSystem::buy(std::string stockCode, int count, int price)
{
	if (stockCode == "") return false;
	if (count < 1) return false;
	if (price < 1) return false;
	return brockerDriver->buy(stockCode, count, price);
}