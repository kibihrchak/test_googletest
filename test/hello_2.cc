#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <any>
#include <variant>
#include <iostream>

namespace
{
using Variant_t = std::variant<int, double>;
using Table_t = std::map<Variant_t, std::any>;

struct IFoo
{
    virtual bool foo(Table_t &t) = 0;
};

struct MockFoo : public IFoo
{
    MOCK_METHOD(bool, foo, (Table_t & t), (override));
};

template <typename T>
bool checkItem(Table_t &table, Variant_t key, T value)
{
    auto mapIterator = table.find(key);

    if (mapIterator == table.end())
    {
        return false;
    }

    if (mapIterator->second.type() != typeid(T))
    {
        std::cout << "Type is " << mapIterator->second.type().name() << std::endl;
    }

    if (std::any_cast<T>(mapIterator->second) != value)
    {
        std::cout << "Got " << std::any_cast<T>(mapIterator->second) << std::endl;
        return false;
    }

    return true;
}

MATCHER(CheckTable, "Check Table_t")
{
    return checkItem(arg, Variant_t(12), std::string("foo")) &&
           checkItem(arg, Variant_t(2.3), 15);
}
} // namespace

TEST(Hello_Googletest, Hello_2)
{
    MockFoo fooObj;

    Table_t test;
    test.insert({12, std::string("foo")});
    test.insert({2.3, 15});

    EXPECT_CALL(fooObj, foo(CheckTable())).WillOnce(::testing::Return(true));

    EXPECT_TRUE(fooObj.foo(test));
}
