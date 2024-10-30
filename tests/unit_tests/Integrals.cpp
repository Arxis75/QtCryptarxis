#include <gtest/gtest.h>
#include <data/byteSet.h>
#include <type_traits>

// Helper function to test if a type can be constructed with a specific value
template <typename T, typename... Args>
constexpr bool is_constructible_with_value(Args&&... args) {
    return std::is_constructible_v<T, Args...>;
}

TEST(IntegralsTests, Constructors_Capabilities)
{
    uint8_t ptr[3] = {0x00, 0x01, 0x02};
    uint64_t medium_integer = 0x123456789ABCDEF;
    Integer large_integer("115792089237316195423570985008687907853269984665640564039457584007908834671663");
    string str("0x123456789ABCDEF");

    //Mandatory constructions
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(ptr, sizeof(ptr)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(""));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>("discv5"));
    //Forbidden constructions
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(0));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(0, 32));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(0x123456789ABCDEF));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(0x123456789ABCDEF, 17));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(medium_integer));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(medium_integer, 17));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(Integer::zero));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(Integer::zero, 17));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(large_integer));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(large_integer, 17));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>("", 17));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>("0x123456789ABCDEF", 17));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(str));
    ASSERT_EQ(true, !is_constructible_with_value<ValueVector<byteSet>>(str, 17));
    // Casting solves the forbidden constructions
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(0)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(0, 32)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(0x123456789ABCDEF)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(0x123456789ABCDEF, 17)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(medium_integer)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(medium_integer, 17)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(Integer::zero)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(Integer::zero, 17)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(large_integer)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSet(large_integer, 17)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSetView("", 17)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSetView("0x123456789ABCDEF", 17)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSetView(str)));
    ASSERT_EQ(true, is_constructible_with_value<ValueVector<byteSet>>(byteSetView(str, 17)));

    //Mandatory constructions
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(0));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(0, 32));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(0x123456789ABCDEF));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(0x123456789ABCDEF, 17));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(medium_integer));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(medium_integer, 17));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(Integer::zero));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(Integer::zero, 17));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(large_integer));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(large_integer, 17));
    //Forbidden constructions
    ASSERT_EQ(true, !is_constructible_with_value<byteSet<>>(ptr, sizeof(ptr)));
    ASSERT_EQ(true, !is_constructible_with_value<byteSet<>>(""));
    ASSERT_EQ(true, !is_constructible_with_value<byteSet<>>("", 17));
    ASSERT_EQ(true, !is_constructible_with_value<byteSet<>>("0x123456789ABCDEF"));
    ASSERT_EQ(true, !is_constructible_with_value<byteSet<>>("0x123456789ABCDEF", 17));
    ASSERT_EQ(true, !is_constructible_with_value<byteSet<>>(str));
    ASSERT_EQ(true, !is_constructible_with_value<byteSet<>>(str, 17));
    // Casting solves the forbidden constructions
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(ValueVector<byteSet>(ptr, sizeof(ptr))));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(byteSetView("")));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(byteSetView("", 17)));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(byteSetView("0x123456789ABCDEF")));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(byteSetView("0x123456789ABCDEF", 17)));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(byteSetView(str)));
    ASSERT_EQ(true, is_constructible_with_value<byteSet<>>(byteSetView(str, 17)));

    //Mandatory constructions
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(""));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>("", 17));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>("0x123456789ABCDEF"));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>("0x123456789ABCDEF", 17));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(str));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(str, 17));
    //Forbidden constructions
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(ptr, sizeof(ptr)));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(0));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(0, 32));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(0x123456789ABCDEF));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(0x123456789ABCDEF, 17));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(medium_integer));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(medium_integer, 17));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(Integer::zero));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(Integer::zero, 17));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(large_integer));
    ASSERT_EQ(true, !is_constructible_with_value<byteSetView<>>(large_integer, 17));
    // Casting solves the forbidden constructions
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(ValueVector<byteSet>(ptr, sizeof(ptr))));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(0)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(0, 32)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(0x123456789ABCDEF)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(0x123456789ABCDEF, 17)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(medium_integer)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(medium_integer, 17)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(Integer::zero)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(Integer::zero, 17)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(large_integer)));
    ASSERT_EQ(true, is_constructible_with_value<byteSetView<>>(byteSet(large_integer, 17)));
}
