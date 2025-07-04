#pragma once
#include "stock_broker_driver_interface.h"
#include "nemo_api.cpp"

class NemoDriver : public StockBrokerDriverInterface {
public:
	bool login(const std::string& id, const std::string& pass) override;
	bool buy(const std::string& code, int price, int quantity) override;
	bool sell(const std::string& code, int price, int quantity) override;
	int getPrice(const std::string& code) override;

	static const int MIN_GET_PRICE_TIME_IN_MS = 1;
private:
	NemoAPI nemoapi{ NemoAPI() };
};