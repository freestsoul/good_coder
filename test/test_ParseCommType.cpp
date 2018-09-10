#include <string>
#include <gtest/gtest.h>
#include "../src/parse_comm_type.h"

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestParseCommTypeSuite : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(TestParseCommTypeSuite, array_test) {
    const std::string str("11,22,33");
    int* arr_value;
    size_t count;
    myparser::ParseCommType<int>::Instance().parse_comm_type(str, &arr_value, &count);

    ASSERT_EQ(11, arr_value[0]);
    ASSERT_EQ(22, arr_value[1]);
    ASSERT_EQ(33, arr_value[2]);
};
