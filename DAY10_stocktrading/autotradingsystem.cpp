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

bool AutoTradingSystem::login(const std::string& id, const std::string& pass)
{
	if (isInvalidIDorPASS(id, pass)) return false;
	return broker->login(id, pass);
}

bool AutoTradingSystem::isInvalidIDorPASS(const std::string& id, const std::string& pass)
{
	return id == "" || pass == "";
}

int AutoTradingSystem::getPrice(const std::string& stockCode)
{
	if (stockCode == "") return WRONG_PRICE;
	return broker->getPrice(stockCode);
}


