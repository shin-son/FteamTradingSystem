#pragma once
#include "stock_broker_driver_interface.h"
#include "Kiwer_api.cpp"

class KiwerDriver : public StockBrokerDriverInterface {
public:
    bool login(const std::string& id, const std::string& pass) override;
    bool buy(const std::string& code, int price, int quantity) override;
    bool sell(const std::string& code, int price, int quantity) override;
    int getPrice(const std::string& code) override;

private:
    KiwerAPI kiwerapi{ KiwerAPI() };
};
