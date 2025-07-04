#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include "stock_broker_driver_interface.h"
#include "kiwer_driver.h"
#include "nemo_driver.h"
#include "mock_driver.h"

using std::string;

class stockBrockerFactory
{
public:
	static StockBrokerDriverInterface* getInstance(const string& brockerName);

private:
};
