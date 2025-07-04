#pragma once
#include "stock_broker_driver_interface.h"
#include "stock_brocker_factory.h"

using std::string;

class AutoTradingSystem
{
public:
	void selectStockBrocker(const string& brockerName);
	void selectStockBrocker(StockBrokerDriverInterface* new_broker);
	bool buy(const string& stockCode, int count, int price);
    bool sell(const string& stockCode, int count, int price);
	bool login(const std::string& id, const std::string& pass);
	int getPrice(const string& stockCode);
	bool buyNiceTiming(const string& stockCode, int price);

private:
	static const int WRONG_PRICE = -1;
	const int NICE_TIMING_COUNT = 3;
	const int MAXIMUM_QUANTITY = 10000;
	StockBrokerDriverInterface* brockerDriver;

	bool isInvalidIDorPASS(const std::string& id, const std::string& pass);
	bool isNiceBuyTiming(const std::string& stockCode);
};