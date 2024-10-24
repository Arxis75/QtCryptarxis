#include <UI/dialog.h>

#include <QApplication>

#include <data/StrByteSet.h>

/*template <class T=uint8_t>
class Container
{
    static_assert(   std::is_same<T, uint8_t>::value
                  || std::is_same<T, char>::value 
                  || std::is_same<T, bool>::value );
    public:
        Container<T>() {}
        Container<T>(const T[]) {}
    
        inline void push_front(T elem) { push_front((Container<T>)vector<T>({elem})); }
        inline void push_back(T elem) { m_vector.push_back(elem); }
        T pop_front();
        T pop_back();

        inline void push_front(const Container<T> &c) { m_vector.insert(m_vector.begin(), c.m_vector.begin(), c.m_vector.end()); }
        inline void push_back(const Container<T> &c) { m_vector.insert(m_vector.end(), c.m_vector.begin(), c.m_vector.end()); }
        Container<T> pop_front(uint64_t nb_element);
        Container<T> pop_back(uint64_t nb_element);
    
        inline T operator[](uint64_t index) const { return m_vector[index]; }

        virtual operator string() const;
        friend ostream& operator<<(ostream& out, const ByteSet& v);

        Container<T> at(const uint64_t offset, const uint64_t nb_element) const { return (Container<T>)vector<T>(m_vector.begin() + offset, m_vector.begin() + offset + nb_element); }

        virtual inline uint64_t elemSize() const { return m_vector.size(); }
        inline void clear() { m_vector.clear(); }
        static ByteSet generateRandom(uint32_t nb_elem);

    private:
        vector<T> m_vector;
};

class bitSet : public Container<bool>
{
    public:
        bitSet() : Container<bool>() {}
};

template <class T = uint8_t>
class byteSet : public Container<T>
{
    static_assert(   std::is_same<T, uint8_t>::value
                  || std::is_same<T, char>::value );
    public:
        byteSet<T>() : Container<T>() {}
};

struct StrHex {
    string header = "0x";
    uint8_t chars_per_byte_of_value = 2;
};
struct StrDec {
    string header = "";
    uint8_t chars_per_byte_of_value = 0;
};
struct StrBin {
    string header = "0b";
    uint8_t chars_per_byte_of_value = 8;
};

template <class T = uint8_t, typename U = StrHex >
class strByteSet : public byteSet<T>
{
    static_assert( (  std::is_same<T, uint8_t>::value
                   || std::is_same<T, char>::value)
                && (  std::is_same<U, StrHex>::value
                   || std::is_same<U, StrDec>::value 
                   || std::is_same<U, StrBin>::value) );
    public:
        strByteSet<T, U>() : byteSet<T>() {}
};

template <typename U = StrBin >
class strBitSet : public bitSet
{
    static_assert(   std::is_same<U, StrHex>::value
                  || std::is_same<U, StrDec>::value 
                  || std::is_same<U, StrBin>::value );
    public:
        strBitSet<U>() : bitSet() {}
};*/

    /*Integer zz; // = 0x123456789ABCDEF;
    mpz_ptr z = zz.get_mpz();
    uint8_t aa[10] = {0x00, 0x00, 0x1, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    mpz_import (z, 20, 1, sizeof(aa[0]), 0, 0, aa);
    bool bb[14] = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    mpz_import(z, 11, 1, sizeof(bb[0]), 0, 0, bb);
    cout << hex << zz << endl;*/

int main(int argc, char *argv[])
{
    /*BinStrBitSet i("0b111111111");
    i.push_back("0b1");
    i.push_front("0b1");
    cout << (string)i << endl;

    BitByteSet j((BinStrBitSet)"0b11111111111");
    cout << (string)j << endl;

    BinStrByteSet k((BinStrByteSet)"0b11111111111");
    cout << (string)k << endl;

    BinStrBitSet l((string)k);
    cout << (string)l << endl;

    cout << i.keccak256() << endl;
    cout << j.keccak256() << endl;
    cout << k.keccak256() << endl;
    cout << l.keccak256() << endl;*/

    /*string str_j = j;
    cout << str_j << endl;
    
    BinStrByteSet bj = j.toBinStrByteSet();
    string str_bj = bj;
    cout << str_bj << endl;

    GWeiStrByteSet i("8.050351573");
    
    string str_i = i;
    cout << str_i << endl;

    HexStrByteSet f("0x0");

    HexStrByteSet x("0x00123456789ABCDEF", 17);
    cout << string(x) << endl;
    //ByteSet x("0x10000000000000009", 17, 16);
    DecStrByteSet y(x);
    cout << string(y) << endl;
    IntByteSet z(y);
    cout << string(z) << endl;*/
    /*string yy = y.toHex();
    yy = y.toDec();
    yy = y.toBin();

    yy = y.toFixedHex(32);
    yy = y.toFixedBin(32);*/

/*    //dec string => hex string
    stringstream ss;
    ss << std::hex << Integer("65535");
    string out = ss.str();

    out = addZeroPadding("0x0000F", 16, 3);

    //hex string => dec string
    out = toHex("zzzzz", 10);
    out = toHex("0x12AB", 10);
    out = toHex("12AB", 10); 
    out = toHex("0x12ab", 10);
    out = toHex("12ab", 10);
    out = toDec("zzzzz", 2);
    out = toHex("0x12AB", 2);
    out = toHex("12AB", 2);
    out = toHex("0x12ab", 2);
    out = toHex("12ab", 2);
    out = toHex("65536", 2);

    out = toDec("zzzzz", 16);
    out = toDec("zzzzz", 2);
    out = toDec("0x12AB", 2);
    out = toDec("12AB", 2);
    out = toDec("0x12ab", 2);
    out = toDec("12ab", 2);
    out = toDec("65536", 2);

    out = toBin("zzzzz", 16);
    out = toBin("zzzzz", 10);
    out = toBin("0x12AB", 10);
    out = toBin("12AB", 10);
    out = toBin("0x12ab", 10);
    out = toBin("12ab", 10);

    //hex string => dec string
    out = toDec(removeBaseHeader("0b111"), 2);
    out = toDec(removeBaseHeader("0b11111"), 2);
    out = toDec(removeBaseHeader("0x12AB"), 16);
    out = toDec("12AB", 16);
    out = toDec(removeBaseHeader("0x12ab"), 16);
    out = toDec("12ab", 16);*/

    QApplication a(argc, argv);
    Dialog d;
    d.show();
    return a.exec();
}