#include "Nemo_driver.h"

bool NemoDriver::login(const std::string& id, const std::string& pass)
{
    nemoapi.certification(id, pass);
    return true;
}

bool NemoDriver::buy(const std::string& code, int price, int quantity)
{
    nemoapi.purchasingStock(code, price, quantity);
    return true;
}

bool NemoDriver::sell(const std::string& code, int price, int quantity)
{
    nemoapi.sellingStock(code, price, quantity);
    return true;
}

int NemoDriver::getPrice(const std::string& code)
{    return nemoapi.getMarketPrice(code, MIN_GET_PRICE_TIME_IN_MS);
}