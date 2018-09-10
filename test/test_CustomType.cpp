#include <gtest/gtest.h>
#include "../src/custom_type.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestCustomTypeExampleSuite : public ::testing::Test{
protected:
    TestCustomTypeExampleSuite(){};
    virtual ~TestCustomTypeExampleSuite(){};
    virtual void SetUp() {}
    virtual void TearDown() {}
};

/**
 * @brief
 * @begin_version
 **/
TEST_F(TestCustomTypeExampleSuite, custom_example)
{
    myparser::CustomTypeExample custom_example;
    myparser::parse_custom_type_example("1|a|1.23", &custom_example);

    ASSERT_EQ(1, custom_example.int_value);
    ASSERT_EQ('a', custom_example.char_value);
    ASSERT_EQ(1.23, custom_example.double_value);
}
