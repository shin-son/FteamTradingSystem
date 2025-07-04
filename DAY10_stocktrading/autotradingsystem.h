#pragma once
#include "stock_broker_driver_interface.h"
#include "stock_brocker_factory.h"

using std::string;

class AutoTradingSystem
{
public:
	void selectStockBrocker(string brokerName);

private:
	std::unique_ptr<StockBrokerDriverInterface> brockerDriver;
};