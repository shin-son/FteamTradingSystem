#pragma once
#include <string>
#include "stock_broker_driver_interface.h"

using std::string;

class AutoTradingSystem
{
public:
	void selectStockBrocker(string brokerName);

private:
	StockBrokerDriverInterface* broker;
};
