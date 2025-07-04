#pragma once
#include "stock_broker_driver_interface.h"

using std::string;

// Mock 클래스 정의
class MockStockBrokerDriver : public StockBrokerDriverInterface {
public:
    MOCK_METHOD(string, selectStockBrocker, (), (const, override));
    MOCK_METHOD(bool, login, (const string& id, const string& pass), (override));
    MOCK_METHOD(bool, buy, (const string& code, int price, int quantity), (override));
    MOCK_METHOD(bool, sell, (const string& code, int price, int quantity), (override));
    MOCK_METHOD(int, getPrice, (const string& code), (override));
};