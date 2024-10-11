#include <gtest/gtest.h>
#include <data/BitSet.h>

TEST(BitSet_tests, BitSet_Constructors)
{
    BitSet b;
    Integer expected = 0;
    Integer actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 0;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = BitSet(Integer(7), 3);
    expected = 7;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 3;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = BitSet(Integer(127), 7);
    expected = 127;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 7;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = BitSet(Integer(255), 8);
    expected = 255;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 8;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = BitSet(Integer(256), 9);
    expected = 256;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 9;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = BitSet(Integer("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095"), 512);
    expected = Integer("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095");
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 512;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);
}

TEST(BitSet_tests, BitSet_pushBackInteger)
{
    // <1-byte + <1-byte = <1-byte
    BitSet b(Integer(7), 3);
    b.push_back(Integer(3),2);
    Integer expected = 31;
    Integer actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 5;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    // <1-byte + <1-byte = 1-byte
    b = BitSet(Integer(7), 3);
    b.push_back(Integer(31),5);
    expected = 255;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 8;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    // <1-byte + <1-byte = >1-byte
    b = BitSet(Integer(7), 3);
    b.push_back(Integer(127),7);
    expected = 1023;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 10;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    //>1-bytes + >1-bytes = 3-bytes
    b = BitSet(Integer(1023), 10);
    b.push_back(Integer(16383),14);
    expected = 16777215;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 24;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    //3-bytes with front 0-padding
    b = BitSet(Integer::zero, 10);
    b.push_back(Integer(16383),14);
    expected = 16383;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 24;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    //3-bytes with back 0-padding
    b = BitSet(Integer(1023), 10);
    b.push_back(Integer::zero,14);
    expected = 16760832;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 24;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);
}

TEST(BitSet_tests, BitSet_pushBackString)
{
    BitSet b;
    b.push_back("10", 2, 2);
    Integer expected = 2;
    Integer actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 2;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("0b10", 2, 2);
    expected = 2;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 2;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("10", 5, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 5;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("0x10", 5, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 5;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("0x10", 8, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 8;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("0x10", 13, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 13;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("0x10", 512, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 512;
    actual = b.bitsize();
    ASSERT_EQ(actual, expected);
}