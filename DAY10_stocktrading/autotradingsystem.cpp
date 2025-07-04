#pragma once
#include "autotradingsystem.h"


void AutoTradingSystem::selectStockBrocker(string brokerName)
{
	brockerDriver = stockBrockerFactory::getInstance(brokerName);
}