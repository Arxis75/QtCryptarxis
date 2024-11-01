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

vector<uint8_t> vec_expected;
const unsigned char arr_10x8[10] = 
                            { 0x07, 'r', 'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
const char* str_10x8 = 
                            "\x07rawstring";
vector<uint8_t> vec_10x8 =   
                            { 0x07, 'r', 'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
vector<uint8_t> vec_11x8 =  
                            { 0x00, 0x07, 'r', 'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
vector<uint8_t> vec_8x8 =  
                            {'a', 'w', 's', 't', 'r', 'i', 'n', 'g'};
vector<uint8_t> vec_2x8 =  
                            {'n', 'g'};
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
Integer int_10x8 = 
                            Integer("35166517413578285870695");
string str_20x4 = 
                            string("0x07726177737472696E67");
string str_19x4 =
                            string("0x7726177737472696E67");
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
    ASSERT_EQ(actual_ByteSet.toV(), vector<uint8_t>({'g'}));
    actual_ByteSet = ByteSet(int_10x8, 2);                
    ASSERT_EQ(actual_ByteSet.toV(), vector<uint8_t>({'n', 'g'}));
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
    ASSERT_EQ(actual_BitSet.toV(), vector<uint8_t>({0b1}));
    actual_BitSet = ByteSet<bool>(int_10x8, 2);                
    ASSERT_EQ(actual_BitSet.toV(), vector<uint8_t>({0b1, 0b1}));
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
    StrByteSet<GWei> actual_GWeiByteSet;
    StrByteSet<GWei, bool> actual_GWeiBitSet;

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
    actual_GWeiByteSet = StrByteSet<GWei>(str_gwei);          
    ASSERT_EQ(actual_GWeiByteSet.toV(), vec_10x8);
    //smaller size specified
    actual_GWeiByteSet = StrByteSet<GWei>(str_gwei, 2);                
    ASSERT_EQ(actual_GWeiByteSet.toV(), vec_2x8);
    //exact size specified
    actual_GWeiByteSet = StrByteSet<GWei>(str_gwei, vec_10x8.size());               
    ASSERT_EQ(actual_GWeiByteSet.toV(), vec_10x8);
    //larger size specified
    actual_GWeiByteSet = StrByteSet<GWei>(str_gwei, vec_11x8.size());               
    ASSERT_EQ(actual_GWeiByteSet.toV(), vec_11x8);

    //Constructors (unaligned) from Gwei String
    //no size specified
    actual_GWeiBitSet = StrByteSet<GWei, bool>(str_gwei);          
    ASSERT_EQ(actual_GWeiBitSet.toV(), vec_75x1);
    //smaller size specified
    actual_GWeiBitSet = StrByteSet<GWei, bool>(str_gwei, 63);                
    ASSERT_EQ(actual_GWeiBitSet.toV(), vec_63x1);
    //exact size specified
    actual_GWeiBitSet = StrByteSet<GWei, bool>(str_gwei, vec_80x1.size());               
    ASSERT_EQ(actual_GWeiBitSet.toV(), vec_80x1);
    //larger size specified
    actual_GWeiBitSet = StrByteSet<GWei, bool>(str_gwei, vec_83x1.size());               
    ASSERT_EQ(actual_GWeiBitSet.toV(), vec_83x1);
}