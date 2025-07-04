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
    bool sell(std::string stockCode, int count, int price);
	bool login(const std::string& id, const std::string& pass);
	int getPrice(const string& stockCode);

private:
	static const int WRONG_PRICE = -1;
	StockBrokerDriverInterface* brockerDriver;

	bool isInvalidIDorPASS(const std::string& id, const std::string& pass);
};
