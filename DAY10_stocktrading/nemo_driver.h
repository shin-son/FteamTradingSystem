#pragma once
#include "stock_broker_driver_interface.h"
#include "nemo_api.cpp"

class NemoDriver : public StockBrokerDriverInterface {
public:
    // StockBrokerDriverInterface��(��) ���� ��ӵ�
    std::string selectStockBrocker() const override
    {
        return "�׸�";
    }

    bool login(const std::string& id, const std::string& pass) override
    {
        nemoapi.certification(id, pass);
        return true;
    }

    bool buy(const std::string& code, int price, int quantity) override
    {
        return false;
    }

    bool sell(const std::string& code, int price, int quantity) override
    {
        return false;
    }

    int getPrice(const std::string& code) override
    {
        return 0;
    }
private:
    NemoAPI nemoapi{ NemoAPI() };
};