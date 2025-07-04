#pragma once
#include "autotradingsystem.h"
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

void AutoTradingSystem::selectStockBrocker(const string& brockerName)
{
	brockerDriver = stockBrockerFactory::getInstance(brockerName);
}

void AutoTradingSystem::selectStockBrocker(StockBrokerDriverInterface* new_broker)
{
	brockerDriver = new_broker;
}

bool AutoTradingSystem::buy(const string& stockCode, int count, int price)
{
	if (stockCode == "") return false;
	if (count < 1) return false;
	if (price < 1) return false;

	return brockerDriver->buy(stockCode, count, price);
}

bool AutoTradingSystem::sell(const string& stockCode, int count, int price)
{
	if (stockCode == "") return false;
	if (count < 1) return false;
	if (price < 1) return false;
	return brockerDriver->sell(stockCode, count, price);
}

bool AutoTradingSystem::login(const std::string& id, const std::string& pass)
{
	if (isInvalidIDorPASS(id, pass)) return false;
	return brockerDriver->login(id, pass);
}

bool AutoTradingSystem::isInvalidIDorPASS(const std::string& id, const std::string& pass)
{
	return id == "" || pass == "";
}

int AutoTradingSystem::getPrice(const std::string& stockCode)
{
	if (stockCode == "") return WRONG_PRICE;
	return brockerDriver->getPrice(stockCode);
}

bool AutoTradingSystem::buyNiceTiming(const std::string& stockCode, int price)
{
	if (stockCode == "") return false;
	if (price < 1) return false;
	if (isNiceBuyTiming(stockCode) == false) return false;

	return brockerDriver->buy(stockCode, price, MAXIMUM_QUANTITY);
}

bool AutoTradingSystem::isNiceBuyTiming(const std::string& stockCode)
{
	std::vector<int> priceList;

	for (int count = 0; count < NICE_TIMING_COUNT; count++) {
		priceList.push_back(brockerDriver->getPrice(stockCode));
		Sleep(100);
	}

	for (int count = 0; count < NICE_TIMING_COUNT - 1; count++) {
		if (priceList[count] >= priceList[count + 1]) return false;					
	}

	return true;
}

bool AutoTradingSystem::SellNiceTiming(const std::string stockCode,
                                       int quantity) {
  bool result = false;
  std::vector<int> prices = {0, 0, 0};
  if (stockCode == "") return result;

  if (isNiceSellTiming(prices, stockCode)) {
    int currentPrice = prices[2];
    if (quantity > 0) {
      result = sell(stockCode, currentPrice, quantity);
    }
  }
  return result;
}

bool AutoTradingSystem::isNiceSellTiming(std::vector<int> prices,
                                         const std::string stockCode) {
  for (int i = 0; i < 3; ++i) {
    prices.push_back(getPrice(stockCode));
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  if (prices[0] > prices[1] && prices[1] > prices[2]) return true;
  return false;