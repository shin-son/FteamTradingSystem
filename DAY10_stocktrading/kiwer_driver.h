#ifndef KIWER_DRIVER_H
#define KIWER_DRIVER_H

#include "kiwer_api.cpp"
#include "stocker_interface.h"

class KiwerDriver : public StockerBrokerDriverInterface {
 public:
  explicit KiwerDriver(KiwerAPI* api);
  ~KiwerDriver();

  bool login(const string& id, const string& pw) override;
  bool buy(const string& code, int price, int qty) override;
  bool sell(const string& code, int price, int qty) override;
  int getPrice(const string& code) override;
  string selectStockBrocker() const override;
  string getBrokerName() const override;

 private:
  KiwerAPI* api_;
};
#pragma once
