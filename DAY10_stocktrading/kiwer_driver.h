#pragma once
#include "stock_broker_driver_interface.h"
#include "Kiwer_api.cpp"

class KiwerDriver : public StockBrokerDriverInterface {
 public:
  bool login(const std::string& id, const std::string& pass) override
  {
    kiwerapi.login(id, pass);
    return true;
  }

  bool buy(const std::string& code, int price, int quantity) override
  {
    return false;
  }

  bool sell(const std::string& code, int price, int quantity) override
  {
    if (code.empty() || code == "999999") return false;
    if (price < 1) return false;
    if (quantity < 1) return false;
    kiwerapi.sell(code, quantity, price);
    return true;
      return false;
  }

  int getPrice(const std::string& code) override
  {
	  return 0;
  }

 private:
  KiwerAPI kiwerapi{KiwerAPI()};
};
