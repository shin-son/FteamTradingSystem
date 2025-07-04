#pragma once
#include <string>
#include "StockBrokerDriverInterface.h"

using std::string;

class AutoTradingSystem
{
public:
	void selectStockBrocker(string brokerName);

private:
	StockBrokerDriverInterface* broker;
};