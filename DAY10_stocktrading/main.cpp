#include "gmock/gmock.h"
#include "autotradingsystem.h"
#include "stock_broker_driver_interface.h"
#include "mock_driver.h"

#include <string>
#include <vector>

using namespace testing;
using namespace std;

class stockBrockerFixture : public Test {
public:

private:


};

TEST(stockBrocker, SelectKiwerBrocker) {
    AutoTradingSystem autoTradingSystem;

    try {
        autoTradingSystem.selectStockBrocker("키워");
    }
    catch (std::exception& e)
    {
        FAIL();
    }
}

TEST(stockBrocker, SelectNemoBrocker) {
    AutoTradingSystem autoTradingSystem;

    try {
        autoTradingSystem.selectStockBrocker("네모");
    }
    catch (std::exception& e)
    {
        FAIL();
    }
}

TEST(stockBrocker, SelectInvalidBrocker) {
    AutoTradingSystem autoTradingSystem;

    try {
        autoTradingSystem.selectStockBrocker("과거");
        FAIL();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

TEST(stockBrocker, LoginSuccess) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string id = "myid";
    string pass = "mypass";

    // login 함수가 특정 인자에 대해 true를 반환하도록 설정
    EXPECT_CALL(mock, login(id, pass)).Times(1)
        .WillOnce(Return(true));

    EXPECT_EQ(ATS.login(id, pass), true);
}

TEST(stockBrocker, LoginFailure) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string id = "wrongid";
    string pass = "wrongpass";

    // 잘못된 아이디/비번으로 로그인 실패 리턴
    EXPECT_CALL(mock, login(id, pass)).Times(1)
        .WillOnce(Return(false));

    EXPECT_EQ(ATS.login(id, pass), false);
}

TEST(stockBrocker, BuySuccess) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";  // 삼성전자
    int price = 70000;
    int quantity = 10;

    // 이 매개변수 조합에 대해 true를 반환
    EXPECT_CALL(mock, buy(code, price, quantity)).Times(1)
        .WillOnce(Return(true));

    EXPECT_EQ(true, ATS.buy(code, price, quantity));
}

TEST(stockBrocker, BuyFailure) {
    AutoTradingSystem ATS;
    NiceMock<MockStockBrokerDriver> mock;
    ATS.selectStockBrocker(&mock);

    string wrong_code = "000000";  // 잘못된 종목 코드
    int price = 70000;
    int quantity = 10;

    // 이 매개변수 조합에 대해 true를 반환
    EXPECT_CALL(mock, buy(wrong_code, price, quantity)).Times(1)
        .WillOnce(Return(false));

    EXPECT_EQ(false, ATS.buy(wrong_code, price, quantity));
}

TEST(stockBrocker, SellSuccess) {
    AutoTradingSystem ATS;
    NiceMock<MockStockBrokerDriver> mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";  // 예: 삼성전자
    int price = 71000;
    int quantity = 5;

    // 지정된 인자에 대해 true 리턴 설정
    EXPECT_CALL(mock, sell(code, price, quantity))
        .WillOnce(Return(true));

    EXPECT_TRUE(ATS.sell(code, price, quantity));
}

TEST(stockBrocker, SellFailure) {
    AutoTradingSystem ATS;
    NiceMock<MockStockBrokerDriver> mock;
    ATS.selectStockBrocker(&mock);

    string wrong_code = "00000";  // 잘못된 종목
    int price = 30000;
    int quantity = 100;

    // 실패 조건에 대해 false 반환 설정
    EXPECT_CALL(mock, sell(wrong_code, price, quantity))
        .WillOnce(Return(false));

    EXPECT_FALSE(ATS.sell(wrong_code, price, quantity));
}

TEST(stockBrocker, GetPriceReturnsCorrectValue) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";  // 예: 삼성전자
    int expectedPrice = 71500;

    // mock이 해당 종목 코드에 대해 expectedPrice를 반환하도록 설정
    EXPECT_CALL(mock, getPrice(code))
        .Times(1)
        .WillOnce(Return(expectedPrice));

    int ret = ATS.getPrice(code);

	EXPECT_EQ(ret, expectedPrice);
}

TEST(stockBrocker, GetPriceReturnsZeroForInvalidCode) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "999999";  // 잘못된 종목

    // 잘못된 코드에 대해서는 -1 반환하도록 설정
    EXPECT_CALL(mock, getPrice(code))
        .Times(1)
        .WillOnce(Return(-1));

    int ret = ATS.getPrice(code);
    
	EXPECT_EQ(ret, -1);
}

TEST(stockBrocker, BuyNiceTimingShoudBuyWhenPriceIsRising) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";
    int cash = 300000;

    EXPECT_CALL(mock, getPrice(code)).Times(3)
        .WillOnce(Return(68000))
        .WillOnce(Return(69000))
        .WillOnce(Return(70000));

    EXPECT_CALL(mock, buy(code, 300000, _)).Times(1)
        .WillOnce(Return(true));

    EXPECT_EQ(true, ATS.buyNiceTiming(code, cash));
}

TEST(stockBrocker, BuyNiceTimingShoudNotBuyWhenAllPriceIsNotRising) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";
    int cash = 300000;

    EXPECT_CALL(mock, getPrice(code)).Times(3)
        .WillOnce(Return(68000))
        .WillOnce(Return(69000))
        .WillOnce(Return(68000));

    EXPECT_CALL(mock, buy(_, _, _)).Times(0);

    EXPECT_EQ(false, ATS.buyNiceTiming(code, cash));
}

TEST(stockBrocker, BuyNiceTimingShouldNotBuyWhenCashTooLow) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";
    int cash = 260000;

    EXPECT_CALL(mock, getPrice(code)).Times(3)
        .WillOnce(Return(68000))
        .WillOnce(Return(69000))
        .WillOnce(Return(68000));

    EXPECT_CALL(mock, buy(_, _, _)).Times(0);

    EXPECT_EQ(false, ATS.buyNiceTiming(code, cash));
}

TEST(stockBrocker, SellNiceTimingShoudSellWhenPriceIsFalling) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";
    int quantity = 5;
    int last_price = 70000;

    EXPECT_CALL(mock, getPrice(code)).Times(3)
        .WillOnce(Return(72000))
        .WillOnce(Return(71000))
        .WillOnce(Return(70000));

    EXPECT_CALL(mock, sell(code, last_price, 5)).Times(1);

    EXPECT_FALSE(ATS.SellNiceTiming(code, quantity));

}

TEST(stockBrocker, SellNiceTimingShoudNotSellWhenPriceIsRising) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";
    int quantity = 5;
    int last_price = 70000;

    EXPECT_CALL(mock, getPrice(code)).Times(3)
        .WillOnce(Return(70000))
        .WillOnce(Return(71000))
        .WillOnce(Return(72000));

    EXPECT_CALL(mock, sell(code, last_price, 5)).Times(0);

    EXPECT_FALSE(ATS.SellNiceTiming(code, quantity));
}

TEST(stockBrocker, SellNiceTimingShoudNotSellWhenPriceCheckFails) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;
    ATS.selectStockBrocker(&mock);

    string code = "005930";
    int quantity = 5;
    int last_price = 70000;

    EXPECT_CALL(mock, getPrice(code)).Times(3)
        .WillOnce(Return(70000))
        .WillOnce(Return(-1))
        .WillOnce(Return(72000));

    EXPECT_CALL(mock, sell(code, last_price, 5)).Times(0);

    EXPECT_FALSE(ATS.SellNiceTiming(code, quantity));
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}