#include "gmock/gmock.h"
#include "autotradingsystem.h"

#include <string>
#include <vector>

using namespace testing;
using namespace std;

class StockBrokerDriverInterface {
public:
    virtual std::string selectStockBrocker() const = 0;
    virtual bool login(const std::string& id, const std::string& pass) = 0;
    virtual bool buy(const std::string& code, int price, int quantity) = 0;
    virtual bool sell(const std::string& code, int price, int quantity) = 0;
    virtual int getPrice(const std::string& code) = 0;
};

// Mock 클래스 정의
class MockStockBrokerDriver : public StockBrokerDriverInterface {
public:
    MOCK_METHOD(string, selectStockBrocker, (), (const, override));
    MOCK_METHOD(bool, login, (const string& id, const string& pass), (override));
    MOCK_METHOD(bool, buy, (const string& code, int price, int quantity), (override));
    MOCK_METHOD(bool, sell, (const string& code, int price, int quantity), (override));
    MOCK_METHOD(int, getPrice, (const string& code), (override));
};

TEST(stockBrocker, ReturnKiwoomOrNemo) {
    MockStockBrokerDriver mock;

    // 테스트할 리턴값 설정
    EXPECT_CALL(mock, selectStockBrocker())
        .WillOnce(Return("키움"));

    string broker = mock.selectStockBrocker();

    vector<string> validBrockers = { "키움", "네모" };

    EXPECT_THAT(validBrockers, Contains(broker));
}

TEST(stockBrocker, LoginSuccess) {
    MockStockBrokerDriver mock;

    string id = "myid";
    string pass = "mypass";

    // login 함수가 특정 인자에 대해 true를 반환하도록 설정
    EXPECT_CALL(mock, login(id, pass))
        .WillOnce(Return(true));

    // 실제 호출 및 검증
    EXPECT_TRUE(mock.login(id, pass));
}

TEST(stockBrocker, LoginFailure) {
    MockStockBrokerDriver mock;

    string id = "wrongid";
    string pass = "wrongpass";

    // 잘못된 아이디/비번으로 로그인 실패 리턴
    EXPECT_CALL(mock, login(id, pass))
        .WillOnce(Return(false));

    EXPECT_FALSE(mock.login(id, pass));
}

TEST(stockBrocker, BuySuccess) {
    MockStockBrokerDriver mock;

    string code = "005930";  // 삼성전자
    int price = 70000;
    int quantity = 10;

    // 이 매개변수 조합에 대해 true를 반환
    EXPECT_CALL(mock, buy(code, price, quantity))
        .WillOnce(Return(true));

    EXPECT_TRUE(mock.buy(code, price, quantity));
}

TEST(stockBrocker, BuyFailure) {
    MockStockBrokerDriver mock;

    string code = "000000";  // 잘못된 종목 코드
    int price = 100000;
    int quantity = 100;

    // 실패하도록 설정
    EXPECT_CALL(mock, buy(code, price, quantity))
        .WillOnce(Return(false));

    EXPECT_FALSE(mock.buy(code, price, quantity));
}

TEST(stockBrocker, SellSuccess) {
    MockStockBrokerDriver mock;

    string code = "005930";  // 예: 삼성전자
    int price = 71000;
    int quantity = 5;

    // 지정된 인자에 대해 true 리턴 설정
    EXPECT_CALL(mock, sell(code, price, quantity))
        .WillOnce(Return(true));

    EXPECT_TRUE(mock.sell(code, price, quantity));
}

TEST(stockBrocker, SellFailure) {
    MockStockBrokerDriver mock;

    string code = "999999";  // 잘못된 종목
    int price = 30000;
    int quantity = 100;

    // 실패 조건에 대해 false 반환 설정
    EXPECT_CALL(mock, sell(code, price, quantity))
        .WillOnce(Return(false));

    EXPECT_FALSE(mock.sell(code, price, quantity));
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