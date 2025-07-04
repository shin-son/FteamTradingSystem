#pragma once
#include <string>
#include "gmock/gmock.h"

class StockBrokerDriverInterface {
public:
    virtual bool login(const std::string& id, const std::string& pass) = 0;
    virtual bool buy(const std::string& code, int price, int quantity) = 0;
    virtual bool sell(const std::string& code, int price, int quantity) = 0;
    virtual int getPrice(const std::string& code) = 0;
};
