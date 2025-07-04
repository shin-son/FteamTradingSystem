#include "Kiwer_Driver.h"

bool KiwerDriver::login(const std::string& id, const std::string& pass)
{
    kiwerapi.login(id, pass);
    return true;
}

bool KiwerDriver::buy(const std::string& code, int price, int quantity)
{
    kiwerapi.buy(code, quantity, price);
    return true;
}

bool KiwerDriver::sell(const std::string& code, int price, int quantity)
{
    kiwerapi.sell(code, quantity, price);
    return true;
}

int KiwerDriver::getPrice(const std::string& code)
{
    return kiwerapi.currentPrice(code);
}