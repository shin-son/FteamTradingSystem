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

bool AutoTradingSystem::sell(std::string stockCode, int count, int price)
{
	if (stockCode == "") return false;
	if (count < 1) return false;
	if (price < 1) return false;
	return brockerDriver->sell(stockCode, count, price);
}

bool AutoTradingSystem::login(const std::string& id, const std::string& pass)
{
	if (isInvalidIDorPASS(id, pass)) return false;
	return brockerDriver->login(id, pass);
}

bool AutoTradingSystem::isInvalidIDorPASS(const std::string& id, const std::string& pass)
{
	return id == "" || pass == "";
}

int AutoTradingSystem::getPrice(const std::string& stockCode)
{
	if (stockCode == "") return WRONG_PRICE;
	return brockerDriver->getPrice(stockCode);
}
