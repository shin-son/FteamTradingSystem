#include "gmock/gmock.h"
#include "autotradingsystem.h"
#include "stock_broker_driver_interface.h"
#include "mock_driver.h"

#include <string>
#include <vector>

using namespace testing;
using namespace std;
/*
TEST(stockBrocker, ReturnKiwoomOrNemo) {
    MockStockBrokerDriver mock;

    // 테스트할 리턴값 설정
    EXPECT_CALL(mock, selectStockBrocker())
        .WillOnce(Return("키움"));

    string broker = mock.selectStockBrocker();

    vector<string> validBrockers = { "키움", "네모" };

    EXPECT_THAT(validBrockers, Contains(broker));
}
*/
TEST(stockBrocker, LoginSuccess) {
    MockStockBrokerDriver mock;

    string id = "myid";
    string pass = "mypass";

    // login 함수가 특정 인자에 대해 true를 반환하도록 설정
    EXPECT_CALL(mock, login(id, pass)).Times(1)
        .WillOnce(Return(true));

    //ATS.login(id, pass);
}

TEST(stockBrocker, LoginFailure) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;

    string id = "wrongid";
    string pass = "wrongpass";

    // 잘못된 아이디/비번으로 로그인 실패 리턴
    EXPECT_CALL(mock, login(id, pass)).Times(1)
        .WillOnce(Return(false));

    //ATS.login(id, pass);
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

    ATS.buy(code, price, quantity);
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

    ATS.buy(wrong_code, price, quantity);
}

TEST(stockBrocker, SellSuccess) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;

    string code = "005930";  // 예: 삼성전자
    int price = 71000;
    int quantity = 5;

    // 지정된 인자에 대해 true 리턴 설정
    EXPECT_CALL(mock, sell(code, price, quantity)).Times(1)
        .WillOnce(Return(true));
    
    //ATS.sell(code, price, quantity);
}

TEST(stockBrocker, SellFailure) {
    AutoTradingSystem ATS;
    MockStockBrokerDriver mock;

    string wrong_code = "999999";  // 잘못된 종목
    int price = 30000;
    int quantity = 100;

    // 실패 조건에 대해 false 반환 설정
    EXPECT_CALL(mock, sell(wrong_code, price, quantity))
        .WillOnce(Return(false));

    //ATS.sell(code, price, quantity);
}

TEST(stockBrocker, GetPriceReturnsCorrectValue) {
    MockStockBrokerDriver mock;

    string code = "005930";  // 예: 삼성전자
    int expectedPrice = 71500;

    // mock이 해당 종목 코드에 대해 expectedPrice를 반환하도록 설정
    EXPECT_CALL(mock, getPrice(code))
        .WillOnce(Return(expectedPrice));

    EXPECT_EQ(mock.getPrice(code), expectedPrice);
}

TEST(stockBrocker, GetPriceReturnsZeroForInvalidCode) {
    MockStockBrokerDriver mock;

    string code = "999999";  // 잘못된 종목

    // 잘못된 코드에 대해서는 -1 반환하도록 설정
    EXPECT_CALL(mock, getPrice(code))
        .WillOnce(Return(-1));

    EXPECT_EQ(mock.getPrice(code), -1);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}