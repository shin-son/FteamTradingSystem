#pragma once
#include <string>
#include "stock_broker_driver_interface.h"

using std::string;

class AutoTradingSystem
{
public:
	void selectStockBrocker(StockBrokerDriverInterface* new_broker);
	bool buy(std::string stockCode, int count, int price);
	int getPrice(const string& stockCode);

private:
	StockBrokerDriverInterface* broker;
};