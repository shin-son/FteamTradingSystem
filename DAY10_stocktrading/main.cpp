#include "gmock/gmock.h"
#include "autotradingsystem.h"

#include <string>
#include <vector>

using namespace testing;
using namespace std;

// Mock 클래스 정의
class MockStockBrokerDriver : public StockBrokerDriverInterface {
public:
    MOCK_METHOD(bool, login, (const string& id, const string& pass), (override));
    MOCK_METHOD(bool, buy, (const string& code, int price, int quantity), (override));
    MOCK_METHOD(bool, sell, (const string& code, int price, int quantity), (override));
    MOCK_METHOD(int, getPrice, (const string& code), (override));
};

//TEST(stockBrocker, ReturnKiwoomOrNemo) {
//    AutoTradingSystem autotradingSystem;
//
//    // 테스트할 리턴값 설정
//    string autotradingSystem.selectStockBrocker("키움");
//
//    vector<string> validBrockers = { "키움", "네모" };
//
//    EXPECT_THAT(validBrockers, Contains(broker));
//}

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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}