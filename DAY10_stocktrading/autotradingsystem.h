#pragma once
#include <string>
#include "stock_broker_driver_interface.h"

using std::string;

class AutoTradingSystem
{
public:
	void selectStockBrocker(StockBrokerDriverInterface* new_broker);
	bool buy(std::string stockCode, int count, int price);
	bool login(const std::string& id, const std::string& pass);

private:
	StockBrokerDriverInterface* broker;

	bool isInvalidIDorPASS(const std::string& id, const std::string& pass);
};