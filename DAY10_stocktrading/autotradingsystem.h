#pragma once
#include "stock_broker_driver_interface.h"
#include "stock_brocker_factory.h"

using std::string;

class AutoTradingSystem
{
public:
	void selectStockBrocker(const string& brockerName);
	void selectStockBrocker(StockBrokerDriverInterface* new_broker);
	bool buy(std::string stockCode, int count, int price);

private:
	//std::unique_ptr<StockBrokerDriverInterface> brockerDriver;
	StockBrokerDriverInterface* brockerDriver;
};