#include "gmock/gmock.h"
#include "autotradingsystem.h"
#include "stock_broker_driver_interface.h"
#include "mock_driver.h"

#include <string>
#include <vector>

using namespace testing;
using namespace std;

class stockBrockerFixture : public Test {
protected:
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;

    const std::string validCode = "005930";
    const std::string invalidCode = "000000";
    const int stockPrice = 70000;
    const int stockQuantity = 5;
    const int remainCash = 300000;

    void SetUp() override {
        ATS.selectStockBrocker(&mock);
    }
};

TEST_F(stockBrockerFixture, SelectKiwerBrocker) {
    try {
        ATS.selectStockBrocker("키워");
    }
    catch (std::exception& e)
    {
        FAIL();
    }
}

TEST_F(stockBrockerFixture, SelectNemoBrocker) {
    try {
        ATS.selectStockBrocker("네모");
    }
    catch (std::exception& e)
    {
        FAIL();
    }
}

TEST_F(stockBrockerFixture, SelectInvalidBrocker) {
    try {
        ATS.selectStockBrocker("과거");
        FAIL();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

TEST_F(stockBrockerFixture, LoginSuccess) {

    string id = "myid";
    string pass = "mypass";

    EXPECT_CALL(mock, login(id, pass)).Times(1)
        .WillOnce(Return(true));

    EXPECT_EQ(ATS.login(id, pass), true);
}

TEST_F(stockBrockerFixture, LoginFailure) {
    string id = "wrongid";
    string pass = "wrongpass";

    EXPECT_CALL(mock, login(id, pass)).Times(1)
        .WillOnce(Return(false));

    EXPECT_EQ(ATS.login(id, pass), false);
}

TEST_F(stockBrockerFixture, BuySuccess) {
    EXPECT_CALL(mock, buy(validCode, stockPrice, stockQuantity)).Times(1)
        .WillOnce(Return(true));

    EXPECT_EQ(true, ATS.buy(validCode, stockPrice, stockQuantity));
}

TEST_F(stockBrockerFixture, BuyFailure) {
    EXPECT_CALL(mock, buy(invalidCode, stockPrice, stockQuantity)).Times(1)
        .WillOnce(Return(false));

    EXPECT_EQ(false, ATS.buy(invalidCode, stockPrice, stockQuantity));
}

TEST_F(stockBrockerFixture, SellSuccess) {
    EXPECT_CALL(mock, sell(validCode, stockPrice, stockQuantity))
        .WillOnce(Return(true));

    EXPECT_TRUE(ATS.sell(validCode, stockPrice, stockQuantity));
}

TEST_F(stockBrockerFixture, SellFailure) {
    EXPECT_CALL(mock, sell(invalidCode, stockPrice, stockQuantity))
        .WillOnce(Return(false));

    EXPECT_FALSE(ATS.sell(invalidCode, stockPrice, stockQuantity));
}

TEST_F(stockBrockerFixture, GetPriceReturnsCorrectValue) {

    EXPECT_CALL(mock, getPrice(validCode))
        .Times(1)
        .WillOnce(Return(stockPrice));

	EXPECT_EQ(ATS.getPrice(validCode), stockPrice);
}

TEST_F(stockBrockerFixture, GetPriceReturnsZeroForInvalidCode) {
    EXPECT_CALL(mock, getPrice(invalidCode))
        .Times(1)
        .WillOnce(Return(-1));
    
	EXPECT_EQ(ATS.getPrice(invalidCode), -1);
}

TEST_F(stockBrockerFixture, BuyNiceTimingShoudBuyWhenPriceIsRising) {

    EXPECT_CALL(mock, getPrice(validCode)).Times(3)
        .WillOnce(Return(68000))
        .WillOnce(Return(69000))
        .WillOnce(Return(70000));

    EXPECT_CALL(mock, buy(validCode, 300000, _)).Times(1)
        .WillOnce(Return(true));

    EXPECT_EQ(true, ATS.buyNiceTiming(validCode, remainCash));
}

TEST_F(stockBrockerFixture, BuyNiceTimingShoudNotBuyWhenAllPriceIsNotRising) {

    EXPECT_CALL(mock, getPrice(validCode)).Times(3)
        .WillOnce(Return(68000))
        .WillOnce(Return(69000))
        .WillOnce(Return(68000));

    EXPECT_CALL(mock, buy(_, _, _)).Times(0);

    EXPECT_EQ(false, ATS.buyNiceTiming(validCode, remainCash));
}

TEST_F(stockBrockerFixture, BuyNiceTimingShouldNotBuyWhenCashTooLow) {

    EXPECT_CALL(mock, getPrice(validCode)).Times(3)
        .WillOnce(Return(160000))
        .WillOnce(Return(169000))
        .WillOnce(Return(168000));

    EXPECT_CALL(mock, buy(_, _, _)).Times(0);
    EXPECT_EQ(false, ATS.buyNiceTiming(validCode, remainCash));
}

TEST_F(stockBrockerFixture, SellNiceTimingShoudSellWhenPriceIsFalling) {

    EXPECT_CALL(mock, getPrice(validCode)).Times(3)
        .WillOnce(Return(72000))
        .WillOnce(Return(71000))
        .WillOnce(Return(70000));

    EXPECT_CALL(mock, sell(validCode, stockPrice, stockQuantity)).Times(1);

    EXPECT_FALSE(ATS.SellNiceTiming(validCode, stockQuantity));
}


TEST_F(stockBrockerFixture, SellNiceTimingShoudNotSellWhenPriceIsRising) {

    EXPECT_CALL(mock, getPrice(validCode)).Times(3)
        .WillOnce(Return(70000))
        .WillOnce(Return(71000))
        .WillOnce(Return(72000));

    EXPECT_CALL(mock, sell(validCode, stockPrice, stockQuantity)).Times(0);

    EXPECT_FALSE(ATS.SellNiceTiming(validCode, stockQuantity));
}

TEST_F(stockBrockerFixture, SellNiceTimingShoudNotSellWhenPriceCheckFails) {
    EXPECT_CALL(mock, getPrice(validCode)).Times(3)
        .WillOnce(Return(70000))
        .WillOnce(Return(-1))
        .WillOnce(Return(72000));

    EXPECT_CALL(mock, sell(validCode, stockPrice, stockQuantity)).Times(0);

    EXPECT_FALSE(ATS.SellNiceTiming(validCode, stockQuantity));
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}