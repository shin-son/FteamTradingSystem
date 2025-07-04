#include "gmock/gmock.h"
#include "autotradingsystem.h"

#include <string>

using namespace testing;
using namespace std;

class AutoTradingSystem {
public:
    std::string selectStockBrocker();                     // 증권사 선택
};

TEST(stockBrocker, ReturnKiwoomOrNemo) {
    AutoTradingSystem ats;
    string broker = ats.selectStockBrocker();

    // 선택 가능한 증권사 리스트
    vector<string> validBrockers = { "키움", "네모" };

    // 리턴된 값이 유효한 증권사인지 확인
    EXPECT_THAT(validBrockers, Contains(broker));
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}