#pragma once
#include "autotradingsystem.h"

void AutoTradingSystem::selectStockBrocker(StockBrokerDriverInterface* new_broker)
{
	broker = new_broker;
}

bool AutoTradingSystem::buy(std::string stockCode, int count, int price)
{
	if (stockCode == "") return false;
	if (count < 1) return false;
	if (price < 1) return false;
	return broker->buy(stockCode, count, price);
}

bool AutoTradingSystem::sell(std::string stockCode, int count, int price)
{
	if (stockCode == "") return false;
	if (count < 1) return false;
	if (price < 1) return false;
	return broker->sell(stockCode, count, price);
}