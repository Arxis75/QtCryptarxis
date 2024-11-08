#include <gtest/gtest.h>
#include <data/ByteSet.h>
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
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ptr, sizeof(ptr)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>("discv5"));
    //Forbidden constructions
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(0));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(0x00, 32));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(0x123456789ABCDEF));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(0x123456789ABCDEF, 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(medium_integer));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(medium_integer, 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(Integer::zero));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(Integer::zero, 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(large_integer));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(large_integer, 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>("", 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>("0x123456789ABCDEF", 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(str));
    ASSERT_EQ(0x01, !is_constructible_with_value<RawByteSet<>>(str, 17));
    // Casting solves the forbidden constructions
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(0)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(0x00, 32)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(0x123456789ABCDEF)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(0x123456789ABCDEF, 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(medium_integer)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(medium_integer, 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(Integer::zero)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(Integer::zero, 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(large_integer)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(ByteSet(large_integer, 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(StrByteSet("", 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(StrByteSet("0x123456789ABCDEF", 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(StrByteSet(str)));
    ASSERT_EQ(0x01, is_constructible_with_value<RawByteSet<>>(StrByteSet(str, 17)));

    //Mandatory constructions
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(0));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(0x00, 32));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(0x123456789ABCDEF));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(0x123456789ABCDEF, 17));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(medium_integer));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(medium_integer, 17));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(Integer::zero));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(Integer::zero, 17));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(large_integer));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(large_integer, 17));
    //Forbidden constructions
    ASSERT_EQ(0x01, !is_constructible_with_value<ByteSet<>>(ptr, sizeof(ptr)));
    ASSERT_EQ(0x01, !is_constructible_with_value<ByteSet<>>(""));
    ASSERT_EQ(0x01, !is_constructible_with_value<ByteSet<>>("", 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<ByteSet<>>("0x123456789ABCDEF"));
    ASSERT_EQ(0x01, !is_constructible_with_value<ByteSet<>>("0x123456789ABCDEF", 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<ByteSet<>>(str));
    ASSERT_EQ(0x01, !is_constructible_with_value<ByteSet<>>(str, 17));
    // Casting solves the forbidden constructions
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(RawByteSet<>(ptr, sizeof(ptr))));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(StrByteSet("")));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(StrByteSet("", 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(StrByteSet("0x123456789ABCDEF")));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(StrByteSet("0x123456789ABCDEF", 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(StrByteSet(str)));
    ASSERT_EQ(0x01, is_constructible_with_value<ByteSet<>>(StrByteSet(str, 17)));

    //Mandatory constructions
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(""));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>("", 17));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>("0x123456789ABCDEF"));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>("0x123456789ABCDEF", 17));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(str));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(str, 17));
    //Forbidden constructions
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(ptr, sizeof(ptr)));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(0));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(0x00, 32));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(0x123456789ABCDEF));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(0x123456789ABCDEF, 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(medium_integer));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(medium_integer, 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(Integer::zero));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(Integer::zero, 17));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(large_integer));
    ASSERT_EQ(0x01, !is_constructible_with_value<StrByteSet<>>(large_integer, 17));
    // Casting solves the forbidden constructions
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(RawByteSet<>(ptr, sizeof(ptr))));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(0)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(0x00, 32)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(0x123456789ABCDEF)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(0x123456789ABCDEF, 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(medium_integer)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(medium_integer, 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(Integer::zero)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(Integer::zero, 17)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(large_integer)));
    ASSERT_EQ(0x01, is_constructible_with_value<StrByteSet<>>(ByteSet(large_integer, 17)));
}

///Nota: all the global variables below represent the same value, which is:
/// const char*: 10 chars       :   "\x07rawstring"
/// int:         75 bits        :   0b111011100100110000101110111011100110111010001110010011010010110111001100111
/// Hex string:  19 Hex nibbles :   "0x7726177737472696e67"
/// It has been chosen randomly so that it spreads among multiple bytes, and is non-aligned, to help find hedge-cases.
/// Some variables though represent this value truncated, sliced, or expanded with a front 0-padding
/// The names of the variables indicate what happened to the value by documenting its specfic type/size.

vector<uint8_t> vec_expected;
const unsigned char arr_10x8[10] = 
                            { 0x07, 'r', 'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
const unsigned char arr_9x8[9] = 
                            { 'r', 'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
const unsigned char arr_3x8_high[3] = 
                            { 'r', 'a', 'w'};
const unsigned char arr_3x8_middle[3] = 
                            { 's', 't', 'r'};
const unsigned char arr_3x8_low[3] = 
                            { 'i', 'n', 'g'};
const char* str_10x8 = 
                            "\x07rawstring";
const char* str_9x8 = 
                            "rawstring";
const char* str_3x8_high = 
                            "raw";
const char* str_3x8_middle = 
                            "str";
const char* str_3x8_low = 
                            "ing";
vector<uint8_t> vec_10x8 =   
                            { 0x07, 'r', 'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
vector<uint8_t> vec_11x8 =  
                            { 0x00, 0x07, 'r', 'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
vector<uint8_t> vec_8x8 =  
                            {'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
vector<uint8_t> vec_2x8 =  
                            {'n', 'g'};
vector<uint8_t> vec_1x8 =  
                            {'g'};
vector<uint8_t> vec_75x1 = 
                            {                                 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01 };
vector<uint8_t> vec_83x1 = 
                            {                                 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01 };
vector<uint8_t> vec_63x1 = 
                            {         0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01 };
vector<uint8_t> vec_80x1 = 
                            {   0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01 };
vector<uint8_t> vec_88x1 =
                            {   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01 };
vector<uint8_t> vec_64x1 = 
                            {   0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
                                0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01,
                                0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01 };
vector<uint8_t> vec_2x1 =  
                            {   0x01, 0x01 };
vector<uint8_t> vec_1x1 =  
                            {   0x01 };
Integer int_10x8 = 
                            Integer("35166517413578285870695");
string str_20x4 = 
                            string("0x07726177737472696e67");
string str_19x4 =
                            string("0x7726177737472696e67");
Integer int_9x8 = 
                            Integer("2109952033490769374823");
Integer int_3x8_high = 
                            Integer("7496055");
Integer int_3x8_middle = 
                            Integer("7566450");
Integer int_3x8_low = 
                            Integer("6909543");
string str_18x4 =
                            string("0x726177737472696e67");
string str_6x4_high =
                            string("0x726177");
string str_6x4_middle =
                            string("0x737472");
string str_6x4_low =
                            string("0x696e67");
string str_dec = 
                            "35166517413578285870695";
string str_gwei = 
                            "35166517413578.285870695";
string str_80x1 =
                            string("0b00000111011100100110000101110111011100110111010001110010011010010110111001100111");
string str_83x1 =
                            string("0b00000000111011100100110000101110111011100110111010001110010011010010110111001100111");
string str_75x1 =
                            string("0b111011100100110000101110111011100110111010001110010011010010110111001100111");
string str_76x1 =
                            string("0b0111011100100110000101110111011100110111010001110010011010010110111001100111");

TEST(IntegralsTests, RawByteSet_Constructors)
{
    RawByteSet actual_RawByteSet;
    RawByteSet<ByteSet, bool> actual_RawBitSet;

    //Empty RawByteSet
    vec_expected.clear();
    actual_RawByteSet = RawByteSet();
    ASSERT_EQ(actual_RawByteSet.toV(), vec_expected);
    actual_RawBitSet = RawByteSet<ByteSet, bool>();
    ASSERT_EQ(actual_RawBitSet.toV(), vec_expected);

    //Copy-constructor "ByteSet => BitSet"
    actual_RawByteSet.fromV(vec_10x8);
    actual_RawBitSet = RawByteSet<ByteSet, bool>(actual_RawByteSet);
    ASSERT_EQ(actual_RawBitSet.toV(), vec_80x1);
    
    //Copy-constructor "BitSet => ByteSet" (forces alignment)
    actual_RawBitSet.fromV(vec_80x1);
    actual_RawByteSet = RawByteSet<ByteSet, uint8_t>(actual_RawBitSet);
    ASSERT_EQ(actual_RawByteSet.toV(), vec_10x8);
    actual_RawBitSet.fromV(vec_75x1);
    actual_RawByteSet = RawByteSet<ByteSet, uint8_t>(actual_RawBitSet);
    ASSERT_EQ(actual_RawByteSet.toV(), vec_10x8);

    //Constructor from Array
    actual_RawByteSet = RawByteSet(arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_RawByteSet.toV(), vec_10x8);
    actual_RawBitSet = RawByteSet<ByteSet, bool>(arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_RawBitSet.toV(), vec_80x1);

    //Constructor from Raw String
    actual_RawByteSet = RawByteSet(str_10x8);
    ASSERT_EQ(actual_RawByteSet.toV(), vec_10x8);
    actual_RawBitSet = RawByteSet<ByteSet, bool>(str_10x8);
    ASSERT_EQ(actual_RawBitSet.toV(), vec_80x1);
}

TEST(IntegralsTests, ByteSet_Constructors)
{
    ByteSet actual_ByteSet;
    ByteSet<bool> actual_BitSet;

    //Empty ByteSet
    vec_expected.clear();
    actual_ByteSet = ByteSet();         
    ASSERT_EQ(actual_ByteSet.toV(), vec_expected);

    //Constructors (aligned) from Integers
    //no size specified
    vec_expected = vec_10x8;
    actual_ByteSet = ByteSet((uint64_t)int_10x8);         
    ASSERT_EQ(actual_ByteSet.toV(), vec_8x8);
    actual_ByteSet = ByteSet(int_10x8);          
    ASSERT_EQ(actual_ByteSet.toV(), vec_10x8);
    //smaller size specified
    actual_ByteSet = ByteSet((uint64_t)int_10x8, 1);      
    ASSERT_EQ(actual_ByteSet.toV(), vec_1x8);
    actual_ByteSet = ByteSet(int_10x8, 2);                
    ASSERT_EQ(actual_ByteSet.toV(), vec_2x8);
    //exact size specified
    actual_ByteSet = ByteSet((uint64_t)int_10x8, vec_8x8.size());      
    ASSERT_EQ(actual_ByteSet.toV(), vec_8x8);
    actual_ByteSet = ByteSet(int_10x8, vec_10x8.size());               
    ASSERT_EQ(actual_ByteSet.toV(), vec_10x8);
    //larger size specified
    actual_ByteSet = ByteSet(int_10x8, vec_11x8.size());               
    ASSERT_EQ(actual_ByteSet.toV(), vec_11x8);

    //Constructors (not aligned) from Integers
    //no size specified
    vec_expected = vec_10x8;
    actual_BitSet = ByteSet<bool>((uint64_t)int_10x8);         
    ASSERT_EQ(actual_BitSet.toV(), vec_63x1);
    actual_BitSet = ByteSet<bool>(int_10x8);          
    ASSERT_EQ(actual_BitSet.toV(), vec_75x1);
    //smaller size specified
    actual_BitSet = ByteSet<bool>((uint64_t)int_10x8, 1);      
    ASSERT_EQ(actual_BitSet.toV(), vec_1x1);
    actual_BitSet = ByteSet<bool>(int_10x8, 2);                
    ASSERT_EQ(actual_BitSet.toV(), vec_2x1);
    //exact size specified
    actual_BitSet = ByteSet<bool>((uint64_t)int_10x8, vec_63x1.size());      
    ASSERT_EQ(actual_BitSet.toV(), vec_63x1);
    actual_BitSet = ByteSet<bool>(int_10x8, vec_75x1.size());               
    ASSERT_EQ(actual_BitSet.toV(), vec_75x1);
    //larger size specified
    actual_BitSet = ByteSet<bool>(int_10x8, vec_83x1.size());               
    ASSERT_EQ(actual_BitSet.toV(), vec_83x1);
}

TEST(IntegralsTests, StrByteSet_Constructors)
{
    StrByteSet actual_HexByteSet;
    StrByteSet<Bin, bool> actual_BinBitSet;
    StrByteSet<Dec> actual_DecByteSet;
    StrByteSet<Dec, bool> actual_DecBitSet;
    StrByteSet<Gwei> actual_GweiByteSet;
    StrByteSet<Gwei, bool> actual_GweiBitSet;

    //Empty Constructors
    vec_expected.clear();
    actual_HexByteSet = StrByteSet();
    ASSERT_EQ(actual_HexByteSet.toV(), vec_expected);
    actual_BinBitSet = StrByteSet();
    ASSERT_EQ(actual_BinBitSet.toV(), vec_expected);
    actual_HexByteSet = StrByteSet("");
    ASSERT_EQ(actual_HexByteSet.toV(), vec_expected);
    actual_BinBitSet = StrByteSet("");
    ASSERT_EQ(actual_BinBitSet.toV(), vec_expected);
    actual_HexByteSet = StrByteSet("", 0);
    ASSERT_EQ(actual_HexByteSet.toV(), vec_expected);
    actual_BinBitSet = StrByteSet("", 0);
    ASSERT_EQ(actual_BinBitSet.toV(), vec_expected);

    //Constructors (aligned) from aligned Hex String
    //no size specified
    actual_HexByteSet = StrByteSet(str_20x4);          
    ASSERT_EQ(actual_HexByteSet.toV(), vec_10x8);
    //smaller size specified
    actual_HexByteSet = StrByteSet(str_20x4, 2);                
    ASSERT_EQ(actual_HexByteSet.toV(), vec_2x8);
    //exact size specified
    actual_HexByteSet = StrByteSet(str_20x4, vec_10x8.size());               
    ASSERT_EQ(actual_HexByteSet.toV(), vec_10x8);
    //larger size specified
    actual_HexByteSet = StrByteSet(str_20x4, vec_11x8.size());               
    ASSERT_EQ(actual_HexByteSet.toV(), vec_11x8);

    //Constructors (unaligned) from aligned Bin String
    //no size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_80x1);          
    ASSERT_EQ(actual_BinBitSet.toV(), vec_80x1);
    //smaller size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_80x1, 64);                
    ASSERT_EQ(actual_BinBitSet.toV(), vec_64x1);
    //exact size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_80x1, vec_80x1.size());               
    ASSERT_EQ(actual_BinBitSet.toV(), vec_80x1);
    //larger size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_80x1, vec_88x1.size());               
    ASSERT_EQ(actual_BinBitSet.toV(), vec_88x1);

    //Constructors (aligned) from unaligned Hex String
    //no size specified
    actual_HexByteSet = StrByteSet(str_19x4);          
    ASSERT_EQ(actual_HexByteSet.toV(), vec_10x8);
    //smaller size specified
    actual_HexByteSet = StrByteSet(str_19x4, 2);                
    ASSERT_EQ(actual_HexByteSet.toV(), vec_2x8);
    //exact size specified
    actual_HexByteSet = StrByteSet(str_19x4, vec_10x8.size());               
    ASSERT_EQ(actual_HexByteSet.toV(), vec_10x8);
    //larger size specified
    actual_HexByteSet = StrByteSet(str_19x4, vec_11x8.size());               
    ASSERT_EQ(actual_HexByteSet.toV(), vec_11x8);

    //Constructors (unaligned) from unaligned Bin String
    //no size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_75x1);          
    ASSERT_EQ(actual_BinBitSet.toV(), vec_75x1);
    //smaller size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_75x1, 63);                
    ASSERT_EQ(actual_BinBitSet.toV(), vec_63x1);
    //exact size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_75x1, vec_75x1.size());               
    ASSERT_EQ(actual_BinBitSet.toV(), vec_75x1);
    //larger size specified
    actual_BinBitSet = StrByteSet<Bin, bool>(str_75x1, vec_83x1.size());               
    ASSERT_EQ(actual_BinBitSet.toV(), vec_83x1);

    //************************* Dec *********************/

    //Constructors (aligned) from decimal String
    //no size specified
    actual_DecByteSet = StrByteSet<Dec>(str_dec);          
    ASSERT_EQ(actual_DecByteSet.toV(), vec_10x8);
    //smaller size specified
    actual_DecByteSet = StrByteSet<Dec>(str_dec, 2);                
    ASSERT_EQ(actual_DecByteSet.toV(), vec_2x8);
    //exact size specified
    actual_DecByteSet = StrByteSet<Dec>(str_dec, vec_10x8.size());               
    ASSERT_EQ(actual_DecByteSet.toV(), vec_10x8);
    //larger size specified
    actual_DecByteSet = StrByteSet<Dec>(str_dec, vec_11x8.size());               
    ASSERT_EQ(actual_DecByteSet.toV(), vec_11x8);

    //Constructors (unaligned) from decimal String
    //no size specified
    actual_DecBitSet = StrByteSet<Dec, bool>(str_dec);          
    ASSERT_EQ(actual_DecBitSet.toV(), vec_75x1);
    //smaller size specified
    actual_DecBitSet = StrByteSet<Dec, bool>(str_dec, 63);                
    ASSERT_EQ(actual_DecBitSet.toV(), vec_63x1);
    //exact size specified
    actual_DecBitSet = StrByteSet<Dec, bool>(str_dec, vec_80x1.size());               
    ASSERT_EQ(actual_DecBitSet.toV(), vec_80x1);
    //larger size specified
    actual_DecBitSet = StrByteSet<Dec, bool>(str_dec, vec_83x1.size());               
    ASSERT_EQ(actual_DecBitSet.toV(), vec_83x1);

    //************************* Gwei *********************/

    //Constructors (aligned) from Gwei String
    //no size specified
    actual_GweiByteSet = StrByteSet<Gwei>(str_gwei);          
    ASSERT_EQ(actual_GweiByteSet.toV(), vec_10x8);
    //smaller size specified
    actual_GweiByteSet = StrByteSet<Gwei>(str_gwei, 2);                
    ASSERT_EQ(actual_GweiByteSet.toV(), vec_2x8);
    //exact size specified
    actual_GweiByteSet = StrByteSet<Gwei>(str_gwei, vec_10x8.size());               
    ASSERT_EQ(actual_GweiByteSet.toV(), vec_10x8);
    //larger size specified
    actual_GweiByteSet = StrByteSet<Gwei>(str_gwei, vec_11x8.size());               
    ASSERT_EQ(actual_GweiByteSet.toV(), vec_11x8);

    //Constructors (unaligned) from Gwei String
    //no size specified
    actual_GweiBitSet = StrByteSet<Gwei, bool>(str_gwei);          
    ASSERT_EQ(actual_GweiBitSet.toV(), vec_75x1);
    //smaller size specified
    actual_GweiBitSet = StrByteSet<Gwei, bool>(str_gwei, 63);                
    ASSERT_EQ(actual_GweiBitSet.toV(), vec_63x1);
    //exact size specified
    actual_GweiBitSet = StrByteSet<Gwei, bool>(str_gwei, vec_80x1.size());               
    ASSERT_EQ(actual_GweiBitSet.toV(), vec_80x1);
    //larger size specified
    actual_GweiBitSet = StrByteSet<Gwei, bool>(str_gwei, vec_83x1.size());               
    ASSERT_EQ(actual_GweiBitSet.toV(), vec_83x1);
}

TEST(IntegralsTests, Major_Operators)
{
    RawByteSet actual_RawByteSet;
    RawByteSet<ByteSet, bool> actual_RawBitSet;
    ByteSet actual_ByteSet;
    ByteSet<bool> actual_BitSet;
    StrByteSet actual_HexByteSet;
    StrByteSet<Hex, bool> actual_HexBitSet;
    StrByteSet<Dec> actual_DecByteSet;
    StrByteSet<Dec, bool> actual_DecBitSet;
    StrByteSet<Gwei> actual_GweiByteSet;
    StrByteSet<Gwei, bool> actual_GweiBitSet;
    StrByteSet<Bin> actual_BinByteSet;
    StrByteSet<Bin, bool> actual_BinBitSet;

    //RawByteSet::Operator (uint8_t*), only for aligned ByteSet
    actual_RawByteSet.resize(sizeof(arr_10x8));
    memcpy(actual_RawByteSet, arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_RawByteSet.toV(), vec_10x8);
    actual_RawBitSet.resize(sizeof(arr_10x8)*8);
    ASSERT_DEATH({memcpy(actual_RawBitSet, arr_10x8, sizeof(arr_10x8));}, "");

    actual_ByteSet.resize(sizeof(arr_10x8));
    memcpy(actual_ByteSet, arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_ByteSet.toV(), vec_10x8);
    actual_BitSet.resize(sizeof(arr_10x8)*8);
    ASSERT_DEATH({memcpy(actual_BitSet, arr_10x8, sizeof(arr_10x8));}, "");

    actual_HexByteSet.resize(sizeof(arr_10x8));
    memcpy(actual_HexByteSet, arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_HexByteSet.toV(), vec_10x8);
    actual_HexBitSet.resize(sizeof(arr_10x8)*8);
    ASSERT_DEATH({memcpy(actual_HexBitSet, arr_10x8, sizeof(arr_10x8));}, "");

    actual_DecByteSet.resize(sizeof(arr_10x8));
    memcpy(actual_DecByteSet, arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_DecByteSet.toV(), vec_10x8);
    actual_DecBitSet.resize(sizeof(arr_10x8)*8);
    ASSERT_DEATH({memcpy(actual_DecBitSet, arr_10x8, sizeof(arr_10x8));}, "");

    actual_GweiByteSet.resize(sizeof(arr_10x8));
    memcpy(actual_GweiByteSet, arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_GweiByteSet.toV(), vec_10x8);
    actual_GweiBitSet.resize(sizeof(arr_10x8)*8);
    ASSERT_DEATH({memcpy(actual_GweiBitSet, arr_10x8, sizeof(arr_10x8));}, "");

    actual_BinByteSet.resize(sizeof(arr_10x8));
    memcpy(actual_BinByteSet, arr_10x8, sizeof(arr_10x8));
    ASSERT_EQ(actual_BinByteSet.toV(), vec_10x8);
    actual_BinBitSet.resize(sizeof(arr_10x8)*8);
    ASSERT_DEATH({memcpy(actual_BinBitSet, arr_10x8, sizeof(arr_10x8));}, "");

    //ByteSet::Operator (int64_t)
    actual_ByteSet = ByteSet();
    ASSERT_EQ((int64_t)actual_ByteSet, -1);
    actual_BitSet = ByteSet<bool>();
    ASSERT_EQ((int64_t)actual_BitSet, -1);

    actual_ByteSet = ByteSet(int_10x8);
    ASSERT_EQ((int64_t)actual_ByteSet, (int64_t)int_10x8);
    actual_BitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((int64_t)actual_BitSet, (int64_t)int_10x8);

    actual_HexByteSet = ByteSet(int_10x8);
    ASSERT_EQ((int64_t)actual_HexByteSet, (int64_t)int_10x8);
    actual_HexBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((int64_t)actual_HexBitSet, (int64_t)int_10x8);

    actual_DecByteSet = ByteSet(int_10x8);
    ASSERT_EQ((int64_t)actual_DecByteSet, (int64_t)int_10x8);
    actual_DecBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((int64_t)actual_DecBitSet, (int64_t)int_10x8);
    
    actual_GweiByteSet = ByteSet(int_10x8);
    ASSERT_EQ((int64_t)actual_GweiByteSet, (int64_t)int_10x8);
    actual_GweiBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((int64_t)actual_GweiBitSet, (int64_t)int_10x8);
    
    actual_BinByteSet = ByteSet(int_10x8);
    ASSERT_EQ((int64_t)actual_BinByteSet, (int64_t)int_10x8);
    actual_BinBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((int64_t)actual_BinBitSet, (int64_t)int_10x8);

    //ByteSet::Operator (Integer)
    actual_ByteSet = ByteSet();
    ASSERT_EQ((Integer)actual_ByteSet, -1);
    actual_BitSet = ByteSet<bool>();
    ASSERT_EQ((Integer)actual_BitSet, -1);

    actual_ByteSet = ByteSet(int_10x8);
    ASSERT_EQ((Integer)actual_ByteSet, int_10x8);
    actual_BitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((Integer)actual_BitSet, int_10x8);

    actual_HexByteSet = ByteSet(int_10x8);
    ASSERT_EQ((Integer)actual_HexByteSet, int_10x8);
    actual_HexBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((Integer)actual_HexBitSet, int_10x8);

    actual_DecByteSet = ByteSet(int_10x8);
    ASSERT_EQ((Integer)actual_DecByteSet, int_10x8);
    actual_DecBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((Integer)actual_DecBitSet, int_10x8);
    
    actual_GweiByteSet = ByteSet(int_10x8);
    ASSERT_EQ((Integer)actual_GweiByteSet, int_10x8);
    actual_GweiBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((Integer)actual_GweiBitSet, int_10x8);
    
    actual_BinByteSet = ByteSet(int_10x8);
    ASSERT_EQ((Integer)actual_BinByteSet, int_10x8);
    actual_BinBitSet = ByteSet<bool>(int_10x8);
    ASSERT_EQ((Integer)actual_BinBitSet, int_10x8);

    //StrByteSet::Operator (String)
    //(string)StrBxxxSet<Hex>
    actual_HexByteSet = StrByteSet(str_19x4);
    ASSERT_EQ((string)actual_HexByteSet, str_20x4);         //byte-alignment
    actual_HexByteSet = StrByteSet<Bin>(str_75x1);
    ASSERT_EQ((string)actual_HexByteSet, str_20x4);         //byte-alignment
    actual_HexBitSet = StrByteSet<Hex, bool>(str_19x4);
    ASSERT_EQ((string)actual_HexBitSet, str_19x4);
    actual_HexBitSet = StrByteSet<Bin, bool>(str_75x1);
    ASSERT_EQ((string)actual_HexBitSet, str_19x4);          //nibble-alignment
    //(string)StrBxxxSet<Dec>
    actual_DecByteSet = StrByteSet<Hex>(str_19x4);
    ASSERT_EQ((string)actual_DecByteSet, str_dec);
    actual_DecByteSet = StrByteSet<Dec>(str_dec);
    ASSERT_EQ((string)actual_DecByteSet, str_dec);
    actual_DecBitSet = StrByteSet<Bin, bool>(str_75x1);
    ASSERT_EQ((string)actual_DecBitSet, str_dec);
    //(string)StrBxxxSet<Gwei>
    actual_GweiByteSet = StrByteSet<Hex>(str_19x4);
    ASSERT_EQ((string)actual_GweiByteSet, str_gwei);
    actual_GweiByteSet = StrByteSet<Gwei>(str_gwei);
    ASSERT_EQ((string)actual_GweiByteSet, str_gwei);
    actual_GweiBitSet = StrByteSet<Bin, bool>(str_75x1);
    ASSERT_EQ((string)actual_GweiBitSet, str_gwei);
    //(string)StrBxxxSet<Bin>
    actual_BinByteSet = StrByteSet(str_19x4);
    ASSERT_EQ((string)actual_BinByteSet, str_80x1);         //byte-alignment     
    actual_BinByteSet = StrByteSet<Bin>(str_75x1);
    ASSERT_EQ((string)actual_BinByteSet, str_80x1);         //byte-alignment      
    actual_BinBitSet = StrByteSet<Hex, bool>(str_19x4);
    ASSERT_EQ((string)actual_BinBitSet, str_76x1);          //nibble-alignment 
    actual_BinBitSet = StrByteSet<Bin, bool>(str_75x1);
    ASSERT_EQ((string)actual_BinBitSet, str_75x1);
}

TEST(IntegralsTests, Push_As_Constructors)
{
    RawByteSet actual_RawByteSet;
    RawByteSet<ByteSet, bool> actual_RawBitSet;
    ByteSet actual_ByteSet;
    ByteSet<bool> actual_BitSet;
    StrByteSet actual_HexByteSet;
    StrByteSet<Hex, bool> actual_HexBitSet;
    StrByteSet<Dec> actual_DecByteSet;
    StrByteSet<Dec, bool> actual_DecBitSet;
    StrByteSet<Gwei> actual_GweiByteSet;
    StrByteSet<Gwei, bool> actual_GweiBitSet;
    StrByteSet<Bin> actual_BinByteSet;
    StrByteSet<Bin, bool> actual_BinBitSet;

    //From array
    vec_expected = RawByteSet(&arr_9x8[0],sizeof(arr_9x8)).toV();
    actual_RawByteSet.clear();
    actual_RawByteSet.push_back(&arr_3x8_middle[0], sizeof(arr_3x8_middle));
    actual_RawByteSet.push_back(&arr_3x8_low[0], sizeof(arr_3x8_low)); 
    actual_RawByteSet.push_front(&arr_3x8_high[0], sizeof(arr_3x8_high));
    ASSERT_EQ(actual_RawByteSet.toV(), vec_expected);
    vec_expected = RawByteSet(arr_3x8_high, sizeof(arr_3x8_high)).toV();
    ASSERT_EQ(actual_RawByteSet.pop_front(sizeof(arr_3x8_high)).toV(), vec_expected);
    vec_expected = RawByteSet(arr_3x8_low, sizeof(arr_3x8_low)).toV();
    ASSERT_EQ(actual_RawByteSet.pop_back(sizeof(arr_3x8_low)).toV(), vec_expected);
    vec_expected = RawByteSet(arr_3x8_middle, sizeof(arr_3x8_middle)).toV();
    ASSERT_EQ(actual_RawByteSet.pop_back(sizeof(arr_3x8_middle)).toV(), vec_expected);
    //From raw string
    vec_expected = RawByteSet(str_9x8).toV();
    actual_RawByteSet.clear();
    actual_RawByteSet.push_back(str_3x8_middle);
    actual_RawByteSet.push_back(str_3x8_low); 
    actual_RawByteSet.push_front(str_3x8_high);
    ASSERT_EQ(actual_RawByteSet.toV(), vec_expected);
    vec_expected = RawByteSet(str_3x8_high).toV();
    ASSERT_EQ(actual_RawByteSet.pop_front(3).toV(), vec_expected);
    vec_expected = RawByteSet(str_3x8_low).toV();
    ASSERT_EQ(actual_RawByteSet.pop_back(3).toV(), vec_expected);
    vec_expected = RawByteSet(str_3x8_middle).toV();
    ASSERT_EQ(actual_RawByteSet.pop_back(3).toV(), vec_expected);
    //From RawByteSet
    vec_expected = RawByteSet(str_9x8).toV();
    actual_RawByteSet.push_back(RawByteSet(str_9x8));
    ASSERT_EQ(actual_RawByteSet.toV(), vec_expected);

    //From uint64_t
    vec_expected = ByteSet(int_9x8).toV();
    actual_ByteSet.clear();
    actual_ByteSet.push_back((uint64_t)int_3x8_middle);
    actual_ByteSet.push_back((uint64_t)int_3x8_low); 
    actual_ByteSet.push_front((uint64_t)int_3x8_high);
    ASSERT_EQ(actual_ByteSet.toV(), vec_expected);
    vec_expected = ByteSet((uint64_t)int_3x8_high).toV();
    ASSERT_EQ(actual_ByteSet.pop_front(3).toV(), vec_expected);
    vec_expected = ByteSet((uint64_t)int_3x8_low).toV();
    ASSERT_EQ(actual_ByteSet.pop_back(3).toV(), vec_expected);
    vec_expected = ByteSet((uint64_t)int_3x8_middle).toV();
    ASSERT_EQ(actual_ByteSet.pop_back(3).toV(), vec_expected);
    //From Integer
    vec_expected = ByteSet(int_9x8).toV();
    actual_ByteSet.clear();
    actual_ByteSet.push_back(int_3x8_middle);
    actual_ByteSet.push_back(int_3x8_low); 
    actual_ByteSet.push_front(int_3x8_high);
    ASSERT_EQ(actual_ByteSet.toV(), vec_expected);
    vec_expected = ByteSet(int_3x8_high).toV();
    ASSERT_EQ(actual_ByteSet.pop_front(3).toV(), vec_expected);
    vec_expected = ByteSet(int_3x8_low).toV();
    ASSERT_EQ(actual_ByteSet.pop_back(3).toV(), vec_expected);
    vec_expected = ByteSet(int_3x8_middle).toV();
    ASSERT_EQ(actual_ByteSet.pop_back(3).toV(), vec_expected);
    //From ByteSet
    vec_expected = ByteSet(int_9x8).toV();
    actual_ByteSet.push_back(ByteSet(int_9x8));
    ASSERT_EQ(actual_ByteSet.toV(), vec_expected);

    //From String
    vec_expected = StrByteSet(str_18x4).toV();
    actual_HexByteSet.clear();
    actual_HexByteSet.push_back(str_6x4_middle);
    actual_HexByteSet.push_back(str_6x4_low); 
    actual_HexByteSet.push_front(str_6x4_high);
    ASSERT_EQ(actual_HexByteSet.toV(), vec_expected);
    vec_expected = StrByteSet(str_6x4_high).toV();
    ASSERT_EQ(actual_HexByteSet.pop_front(3).toV(), vec_expected);
    vec_expected = StrByteSet(str_6x4_low).toV();
    ASSERT_EQ(actual_HexByteSet.pop_back(3).toV(), vec_expected);
    vec_expected = StrByteSet(str_6x4_middle).toV();
    ASSERT_EQ(actual_HexByteSet.pop_back(3).toV(), vec_expected);
    //From StrByteSet
    vec_expected = StrByteSet(str_18x4).toV();
    actual_HexByteSet.push_back(StrByteSet(str_18x4));
    ASSERT_EQ(actual_HexByteSet.toV(), vec_expected);
}