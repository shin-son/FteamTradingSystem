#pragma once
#include <string>

#include "StockBrokerDriverInterface.h"
#include "nemo_api.cpp"

using std::string;

class NemoDriver : public StockBrokerDriverInterface {
 public:
  NemoDriver(NemoAPI* api);

  bool login(const string& id, const string& pw) override;
  bool buy(const string& code, int price, int qty) override {
    if (string(code).empty() || code == "999999") return false;
    api_->sellingStock(code, price, qty);
    return true;
  };
  bool sell(const string& code, int price, int qty) override;
  int getPrice(const string& code) override;

 private:
  NemoAPI* api_;
};