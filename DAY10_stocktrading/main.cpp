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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}