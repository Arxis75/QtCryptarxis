#include <gtest/gtest.h>
#include <data/ByteSet.h>

TEST(ByteSet_tests, ByteSet_Constructors)
{
    ByteSet b;
    Integer expected = 0;
    Integer actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 0;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = ByteSet(Integer(7), 1);
    expected = 7;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 1;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = ByteSet(Integer(256), 2);
    expected = 256;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 2;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b = ByteSet(Integer("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095"), 64);
    expected = Integer("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095");
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 64;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);
}

TEST(ByteSet_tests, ByteSet_pushBackInteger)
{
    // 1-byte + 1-byte = 2-byte
    ByteSet b(Integer(7), 1);
    b.push_back(Integer(3), 1);
    Integer expected = 1795;
    Integer actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 2;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();
    
    //1-bytes with front 0-padding
    b = ByteSet();
    b.push_back(Integer(1), 32);
    expected = 1;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 32;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);
    
    b.clear();

    //3-bytes with front 0-padding
    b = ByteSet(Integer::zero, 3);
    b.push_back(Integer(16383),2);
    expected = 16383;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 5;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    //3-bytes with back 0-padding
    b = ByteSet(Integer(1023), 3);
    b.push_back(Integer::zero,2);
    expected = 67043328;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 5;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);
}

TEST(ByteSet_tests, ByteSet_pushBackString)
{
    ByteSet b;
    b.push_back("10", 1, 2);
    Integer expected = 2;
    Integer actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 1;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("0b10", 1, 2);
    expected = 2;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 1;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("10", 1, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 1;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();

    b.push_back("0x10", 1, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 1;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);

    b.clear();

    //front-0-padding
    b.push_back("0x10", 64, 16);
    expected = 16;
    actual = Integer(b);
    ASSERT_EQ(actual, expected);
    expected = 64;
    actual = b.byteSize();
    ASSERT_EQ(actual, expected);
}