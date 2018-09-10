#include <gtest/gtest.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "../src/parse_custom_type.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestParseCustomTypeSuite : public ::testing::Test{
protected:
    TestParseCustomTypeSuite() {}
    virtual ~TestParseCustomTypeSuite() {}

    virtual void SetUp() {

        myparser::ParseCustomType<myparser::CustomTypeExample>::Func func =
            boost::bind(&myparser::parse_custom_type_example, _1, _2);

        myparser::ParseCustomType<myparser::CustomTypeExample>::Instance().register_custom_func(func);
    }
    virtual void TearDown() {}
};

TEST_F(TestParseCustomTypeSuite, custom_example)
{
    myparser::CustomTypeExample custom_value;
    myparser::ParseCustomType<myparser::CustomTypeExample>::Instance().
        parse_custom_type("44|b|100.4", &custom_value);

    ASSERT_EQ(44, custom_value.int_value);
    ASSERT_EQ('b', custom_value.char_value);
    ASSERT_EQ(100.4, custom_value.double_value);
}
