#include "gmock/gmock.h"
#include "autotradingsystem.h"

#include <string>

using namespace testing;
using namespace std;

class AutoTradingSystem {
public:
    std::string selectStockBrocker();                     // ���ǻ� ����
};

TEST(stockBrocker, ReturnKiwoomOrNemo) {
    AutoTradingSystem ats;
    string broker = ats.selectStockBrocker();

    // ���� ������ ���ǻ� ����Ʈ
    vector<string> validBrockers = { "Ű��", "�׸�" };

    // ���ϵ� ���� ��ȿ�� ���ǻ����� Ȯ��
    EXPECT_THAT(validBrockers, Contains(broker));
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}