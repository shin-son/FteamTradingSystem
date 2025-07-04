#pragma once
#include "kiwer_api.cpp"
#include "StockBrokerDriverInterface.h"
#include <string>

using std::string;

class KiwerDriver : public StockBrokerDriverInterface {
 public:
   KiwerDriver(KiwerAPI* api);

  bool login(const string& id, const string& pw) override;
  bool buy(const string& code, int price, int qty) override;
  bool sell(const string& code, int price, int qty) override {
    // TODO:: Need to define the wrong stock code
    if (string(code).empty() || string(code) == "999999") return false;
    // TODO:: price ? qty? exception ?
    api_->sell(code, qty, price);
    return true;
  };
  int getPrice(const string& code) override;

 private:
  KiwerAPI* api_;
};

