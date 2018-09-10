#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "../src/parser.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class TestParserSplitColumnSuite : public ::testing::Test{
protected:
    TestParserSplitColumnSuite(){}
    virtual ~TestParserSplitColumnSuite(){}

    virtual void SetUp() {
        _test_parser = new myparser::Parser;
    }

    virtual void TearDown() {
        delete _test_parser;
    }

    myparser::Parser *_test_parser;
};

TEST_F(TestParserSplitColumnSuite, case1)
{
    _test_parser->split_line_columns("1\ta\t3.14", "\t");
    std::vector<std::string> columns = _test_parser->get_columns();

    ASSERT_EQ(3, (int)columns.size());
    ASSERT_STREQ("1", columns[0].c_str());
    ASSERT_STREQ("a", columns[1].c_str());
    ASSERT_STREQ("3.14", columns[2].c_str());
}

class TestParserParseCommTypeSuite : public ::testing::Test{
protected:
    TestParserParseCommTypeSuite() {}
    virtual ~TestParserParseCommTypeSuite() {}

    virtual void SetUp() {
        _test_parser = new myparser::Parser;
        _test_parser->split_line_columns("1\tb\t3.14\tteststring\ta,b,c,d", "\t");
    }

    virtual void TearDown() {
        delete _test_parser;
    }

    myparser::Parser *_test_parser;
};

TEST_F(TestParserParseCommTypeSuite, case2)
{
    int int_value;
    int ret_code = _test_parser->parse_comm_type<int>(0, &int_value);
    ASSERT_EQ(0, ret_code);
    ASSERT_EQ(1, int_value);

    char char_value;
    ret_code = _test_parser->parse_comm_type<char>(1, &char_value);
    ASSERT_EQ(0, ret_code);
    ASSERT_EQ('b', char_value);

    double double_value;
    ret_code = _test_parser->parse_comm_type<double>(2, &double_value);
    ASSERT_EQ(0, ret_code);
    ASSERT_EQ(3.14, double_value);

    char* str_value = nullptr;
    ret_code = _test_parser->parse_comm_type<char*>(3, &str_value);
    ASSERT_EQ(0, ret_code);
    ASSERT_STREQ("teststring", str_value);
}


TEST_F(TestParserParseCommTypeSuite, case3)
{
    char* arr_value = nullptr;
    size_t count = 0;
    int ret_code = _test_parser->parse_comm_type<char>(4, &arr_value, &count);
    ASSERT_EQ(0, ret_code);
    ASSERT_EQ('a', arr_value[0]);
    ASSERT_EQ('b', arr_value[1]);
    ASSERT_EQ('c', arr_value[2]);
    ASSERT_EQ('d', arr_value[3]);
}

TEST_F(TestParserParseCommTypeSuite, case4)
{
    char char_value;
    int ret_code = _test_parser->parse_comm_type<char>(7, &char_value);
    ASSERT_EQ(-1, ret_code);
}

class TestParseCustomTypeSuite : public ::testing::Test{
protected:
    TestParseCustomTypeSuite() {}
    virtual ~TestParseCustomTypeSuite() {}
    virtual void SetUp() {
        myparser::ParseCustomType<myparser::CustomTypeExample>::Func func
            = boost::bind(&myparser::parse_custom_type_example, _1, _2);
        myparser::ParseCustomType<myparser::CustomTypeExample>::Instance().register_custom_func(func);

        _test_parser = new myparser::Parser;
        _test_parser->split_line_columns("33,333\t100|c|3.333", "\t");
    }

    virtual void TearDown() {
        delete _test_parser;
    }

    myparser::Parser *_test_parser;
};

TEST_F(TestParseCustomTypeSuite, case5)
{
    myparser::CustomTypeExample custom_value;
    int ret_code = _test_parser->parse_custom_type<myparser::CustomTypeExample>(1, &custom_value);

    ASSERT_EQ(0, ret_code);
    ASSERT_EQ(100, custom_value.int_value);
    ASSERT_EQ('c', custom_value.char_value);
    ASSERT_EQ(3.333, custom_value.double_value);
}
