#include "gmock/gmock.h"
#include "autotradingsystem.h"
#include "stock_broker_driver_interface.h"
#include "mock_driver.h"

#include <string>
#include <vector>

using namespace testing;
using namespace std;

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

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}