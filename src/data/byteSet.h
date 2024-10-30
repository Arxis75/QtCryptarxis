#pragma once

#include <data/System.h>
#include <crypto/System.h>

template <template <typename> class Derived, typename T = uint8_t>
class ValueVector
{
        template<typename U, std::enable_if_t<std::is_integral<U>::value, bool> = true>
            explicit ValueVector(const U& val, uint64_t nb_elem = 0) = delete;
        template<typename U, std::enable_if_t<std::is_same<U, Integer>::value ,bool> = true>
            explicit ValueVector(const U& val, uint64_t nb_elem = 0) = delete;

        ValueVector(const string& p, uint64_t aligned_size) = delete;
        ValueVector(const char* p, uint64_t aligned_size) = delete;
    public:
        //Default Constructors
        ValueVector() { vvalue.reserve(isAligned() ? 32 : 256); }
        //Copy Constructor
        template<template <typename> class D, typename U>
            ValueVector(const ValueVector<D, U>& v);
        //Array-Copy Constructors
        template <typename U> 
            ValueVector(const U *p, uint64_t aligned_size);   // const U* = const uint8_t*, const unsigned char*
        template <typename U> 
            explicit ValueVector(const U *str);               // const U = const char*

        //Const Operators
        inline bool operator==(const ValueVector &v) const { return vvalue == v.vvalue; }
        inline bool operator!=(const ValueVector &v) const { return vvalue != v.vvalue; }
        inline operator const vector<uint8_t>&() const { return vvalue; }
        inline uint8_t operator[](uint64_t elem_index) const { return vvalue[elem_index]; };
        inline operator const unsigned char*() const { assert(isAligned()); return reinterpret_cast<const unsigned char*>(vvalue.data()); }
        virtual operator string() const;

        //Non-const Operators
        inline operator uint8_t*() { assert(isAligned()); return reinterpret_cast<uint8_t*>(vvalue.data()); }

        //Const accessors
        inline bool getBit(uint64_t bit_offset) const { return (1 << (bit_offset % elementBitSize())) & vvalue[(containerBitSize() - 1 - bit_offset) / elementBitSize()]; }
        inline T getElem(uint64_t elem_offset) const { return vvalue[elem_offset]; }
        Derived<T> get(uint64_t elem_offset, const uint64_t nb_element) const;
        inline Derived<T> left(uint64_t nb_element) const { return get(0, nb_element); }
        inline Derived<T> right(uint64_t nb_element) const { return get(nbElements() - nb_element, nb_element); }

        //Container manipulation interface
        inline void resize(uint64_t nb_elem) { vvalue.resize(nb_elem); }
        inline void setBit(uint64_t bit_offset, const bool& bit_value) { bit_value == 0 ? setBit0(bit_offset) : setBit1(bit_offset); }
        inline void setBit0(uint64_t bit_offset) { vvalue[(containerBitSize() - 1 - bit_offset) / elementBitSize()] &= ~(1 << (bit_offset % elementBitSize())); }
        inline void setBit1(uint64_t bit_offset) { vvalue[(containerBitSize() - 1 - bit_offset) / elementBitSize()] |= (1 << (bit_offset % elementBitSize())); }
        inline void setElem(uint64_t elem_offset, const T& elem) { vvalue[elem_offset] = elem; }
        inline void clear() { vvalue.clear(); }

        inline void push_front(T elem) { vvalue.insert(vvalue.begin(), elem); }
        inline void push_back(T elem) { vvalue.push_back(elem); }
        inline T pop_front();
        inline T pop_back();

        inline void push_front(const Derived<T>& subset) { vvalue.insert(vvalue.begin(), subset.vvalue.begin(), subset.vvalue.end()); }
        inline void push_back(const Derived<T>& subset) { vvalue.insert(vvalue.end(), subset.vvalue.begin(), subset.vvalue.end()); }
        Derived<T> pop_front(uint64_t nb_element);
        Derived<T> pop_back(uint64_t nb_element);

        //Property accessors
        inline bool isAligned() const { return typeid(T) == typeid(uint8_t); }
        inline uint64_t nbElements() const { return vvalue.size(); }
        inline uint64_t bytesToNbElements(uint64_t bytes) const { return ((bytes << 3) / elementBitSize()); }
        inline uint8_t elementBitSize() const { return isAligned() ? 8 : 1; }
        inline uint64_t containerBitSize() const { return nbElements()*elementBitSize(); }
        inline uint64_t containerByteSize() const { return (containerBitSize() >> 3) + (containerBitSize()%8 ? 1 : 0); }
        
        //Hash accessors
        inline Derived<uint8_t> sha256() const;
        inline Derived<uint8_t> keccak256() const;

        friend inline ostream& operator<<(ostream& out, const ValueVector& v) { return out << string(v); }

    private:
        vector<uint8_t> vvalue;
};

template <typename T = uint8_t> 
class byteSet : public ValueVector<byteSet, T>
{
        explicit byteSet(uint8_t* val, uint64_t nb_elem) = delete;
        explicit byteSet(const unsigned char* val, uint64_t nb_elem) = delete;

        explicit byteSet(const string& val, uint64_t nb_elem = 0) = delete;
        explicit byteSet(const char* val, uint64_t nb_elem = 0) = delete;
    public:
        //Default constructor
        byteSet() : ValueVector<byteSet, T>() {}
        //Copy Constructors
        template<typename U>
            byteSet(const byteSet<U>& b) : ValueVector<byteSet, T>(b) {}
        template<typename U>
            byteSet(const ValueVector<byteSet, U> &val) : ValueVector<byteSet, T>(val) {}
        //Constructor from integral and bool values
        template<typename U>
            explicit byteSet(const U &val, uint64_t nb_elem = 0);   // U = integral and bool values

        inline operator uint64_t() const { return toInteger(64); }
        inline operator Integer() const { return toInteger(this->containerBitSize()); }
        inline bool operator==(const byteSet &b) const { return this->containerBitSize() == b.containerBitSize() && Integer(*this) == Integer(b); };
        inline bool operator!=(const byteSet &b) const { return !((*this) == b); };

        inline uint64_t getValueNbElem(Integer val) const { return ceil(logtwo(1+val)/this->elementBitSize()); }
        inline T getValueElem(const Integer &val, uint64_t elem_offset) const { return T((Givaro::pow(2,this->elementBitSize())-1) & (val >> (getValueNbElem(val) - 1 - elem_offset) * (this->elementBitSize()))); }

        static byteSet<T> generateRandom(uint64_t nb_element);

    private:
        Integer toInteger(uint64_t nb_right_bits) const;
};

struct ByteSetViewFormat { string Header; uint8_t Base; uint8_t BitsPerChar; regex Regex; bool UpperCase; uint8_t EXP; };

static ByteSetViewFormat Hex  { .Header = "0x", .Base = 16, .BitsPerChar = 4, .Regex = regex("^(0x)?[0-9a-fA-F]+"), .UpperCase = false, .EXP = 0};
static ByteSetViewFormat Dec  { .Header = "",   .Base = 10, .BitsPerChar = 0, .Regex = regex("^[0-9]+"),            .UpperCase = false, .EXP = 0};
static ByteSetViewFormat Wei = Dec;
static ByteSetViewFormat GWei { .Header = "",   .Base = 10, .BitsPerChar = 0, .Regex = regex("^[0-9]+.[0-9]{9}"),   .UpperCase = false, .EXP = 9};
static ByteSetViewFormat Bin  { .Header = "0b", .Base = 2,  .BitsPerChar = 1, .Regex = regex("^(0b)?[0-1]+"),       .UpperCase = false, .EXP = 0};

template <ByteSetViewFormat const & f = Hex, typename T = uint8_t> 
class byteSetView : public byteSet<T>
{
        explicit byteSetView(uint8_t* val, uint64_t nb_elem) = delete;
        explicit byteSetView(const unsigned char* val, uint64_t nb_elem) = delete;

        template<typename U, std::enable_if_t<std::is_integral<U>::value, bool> = true>
            explicit byteSetView(const U& val, uint64_t nb_elem = 0) = delete;
        template<typename U, std::enable_if_t<std::is_same<U, Integer>::value ,bool> = true>
            explicit byteSetView(const U& val, uint64_t nb_elem = 0) = delete;
    public:
        //Default constructor
        byteSetView() : byteSet<T>() {}
        //Copy Constructors
        template<ByteSetViewFormat const & g, typename U>
            byteSetView(const byteSetView<g, U>& b) : byteSet<T>(b) {}
        template<typename U>
            byteSetView(const byteSet<U> &val) : byteSet<T>(val) {}
        template<typename U>
            byteSetView(const ValueVector<byteSet, U> &val) : byteSet<T>(val) {}
        //Constructor from strings
        template<typename U>
            explicit byteSetView(const U&, uint64_t aligned_size = 0);     // U = const string&
        template<typename U>
            explicit byteSetView(const U*, uint64_t aligned_size = 0);     // U = const char*

        inline virtual operator string() const { return toFormat(f); }

        inline string toFormat(const ByteSetViewFormat& format) const { return integerToStr(Integer(*this), format); }

    protected:
        inline uint64_t getStringNbElem(string val) const { return val.size() * f.BitsPerChar / this->elemcontainerBitSize(); }

    private:
        Integer strToInteger(const string& val) const;
        string integerToStr(const Integer& val, const ByteSetViewFormat& format = f) const;

        uint8_t charToDigit(const char &c) const;
        char digitToChar(const uint8_t &n, bool upper_case = f.UpperCase) const;
};

/*********************************************** CONSTRUCTORS ***************************************************** */

template <template <typename> class Derived, typename T>
template<template <typename> class D, typename U>
ValueVector<Derived, T>::ValueVector(const ValueVector<D, U>& v)
{
    if(isAligned() == v.isAligned())
        //Same alignment
        vvalue = v;
    else {
        // Different alignment => Byte-alignment via containerByteSize()
        vvalue.resize((v.containerByteSize() << 3) / elementBitSize());
        for(uint64_t i = 0 ; i < v.containerBitSize() ; i++)
            // bit per bit copy
            setBit(i, v.getBit(i));
    }
}

template <template <typename> class Derived, typename T>
template <typename U>
ValueVector<Derived, T>::ValueVector(const U* p, uint64_t aligned_size)
{
    static_assert(std::is_same<std::decay_t<U>, uint8_t>::value || std::is_same<std::decay_t<U>, unsigned char>::value, "Constructor accepts only const uint8_t*, const unsigned char*");

    ValueVector<Derived, uint8_t> aligned_me;
    for(uint64_t i=0;i<aligned_size;i++) 
        aligned_me.push_back(p[i]);
    resize(aligned_me.containerBitSize() / elementBitSize());
    *this = aligned_me;
}

template <template <typename> class Derived, typename T>
template <typename U>
ValueVector<Derived, T>::ValueVector(const U* str)
    : ValueVector(reinterpret_cast<const uint8_t*>(str), strlen(str))
{
    static_assert(std::is_same<std::decay_t<U>, char>::value, "Constructor accepts only const char*");
}

template<typename T>
template<typename U>
byteSet<T>::byteSet(const U &val, uint64_t nb_elem)
    : ValueVector<byteSet, T>()
{
    static_assert(std::is_integral<U>::value || std::is_integral<bool>::value, "Constructor accepts only integral values");

    uint64_t nb_elem_for_val = this->getValueNbElem(val);
    uint64_t nb_extra_elem = (nb_elem > nb_elem_for_val ? nb_elem - nb_elem_for_val : 0);
    for(uint64_t i=0;i<nb_extra_elem;i++)
        this->push_back(T(0x00));
    for(uint64_t i=0;i<nb_elem_for_val;i++) 
        this->push_back(T(this->getValueElem(val, i)));
}

template<ByteSetViewFormat const & f, typename T>
template<typename U>
byteSetView<f, T>::byteSetView(const U& val, uint64_t nb_elem)
    : byteSet<T>()
{
    static_assert(std::is_same<std::decay_t<U>, string>::value, "Constructor accepts only const string&");

    if( regex_match(val, f.Regex) ) {
        Integer i = strToInteger(val);
        this->push_back(byteSetView(byteSet<T>(i, nb_elem)));
    }
}

template<ByteSetViewFormat const & f, typename T>
template<typename U>
byteSetView<f, T>::byteSetView(const U* val, uint64_t nb_elem)
    : byteSetView((string)val, nb_elem)
{
    static_assert(std::is_same<std::decay_t<U>, char>::value, "Constructor accepts only const char*");
}

/*********************************************** METHODS ***************************************************** */

template <template <typename> class Derived, typename T>
Derived<T> ValueVector<Derived, T>::get(uint64_t elem_offset, const uint64_t nb_element) const
{
    assert(nbElements() >= elem_offset + nb_element);
    Derived<T> ret_value;
    ret_value.pop_back(nbElements() - (elem_offset + nb_element));
    return ret_value;
}

template <template <typename> class Derived, typename T>
Derived<T> ValueVector<Derived, T>::pop_front(uint64_t nb_element) {
    Derived<T> ret_value;
    assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_back(pop_front());
    return ret_value;
}

template <template <typename> class Derived, typename T>
Derived<T> ValueVector<Derived, T>::pop_back(uint64_t nb_element) {
    Derived<T> ret_value;
    assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_front(pop_back());
    return ret_value;
}

template <template <typename> class Derived, typename T>
T ValueVector<Derived, T>::pop_front()
{
    assert(nbElements());
    uint8_t ret_value = vvalue[0];
    vvalue.erase(vvalue.begin());
    return ret_value;
}

template <template <typename> class Derived, typename T>
T ValueVector<Derived, T>::pop_back()
{
    assert(nbElements());
    uint8_t ret_val = vvalue[nbElements()-1];
    vvalue.pop_back();
    return ret_val;
}

template <template <typename> class Derived, typename T>
ValueVector<Derived, T>::operator string() const
{
    stringstream ss;
    for(uint8_t i: vvalue)
        ss << setfill('0') << setw(elementBitSize()>>2) << hex << Integer(i) << ' ';
    return ss.str();
}

template <template <typename> class Derived, typename T>
Derived<uint8_t> ValueVector<Derived, T>::sha256() const
{
    ValueVector<Derived, uint8_t> aligned_me(*this);
    ValueVector<Derived, uint8_t> digest; digest.resize(32);
    SHA256(aligned_me, aligned_me.containerByteSize(), digest);
    return Derived<uint8_t>(digest);
}

template <template <typename> class Derived, typename T>
Derived<uint8_t> ValueVector<Derived, T>::keccak256() const
{
    ValueVector<Derived, uint8_t> aligned_me(*this);
    hash256 h;
    h = ethash::keccak256(aligned_me, aligned_me.containerByteSize());
    return Derived<uint8_t>(ValueVector<Derived, uint8_t>(&h.bytes[0], 32));
}

template<typename T>
Integer byteSet<T>::toInteger(uint64_t nb_right_bits) const
{
    Integer ret_value = 0;
    uint64_t i_end = min(this->nbElements(), nb_right_bits/this->elementBitSize());
    for(uint64_t i=0;i<i_end;i++)
        ret_value += (Integer(this->getElem(this->nbElements()-1-i)) << (i*this->elementBitSize()));
    return ret_value;     
}

template<typename T>
byteSet<T> byteSet<T>::generateRandom(uint64_t nb_element)
{
    int retval = -1;
    ValueVector<byteSet, uint8_t> aligned_random_buffer;
    uint64_t nb_bytes = nb_element / (typeid(T) == typeid(bool) ? 8 : 1);
    aligned_random_buffer.resize(nb_bytes);
    retval = RAND_bytes(aligned_random_buffer, aligned_random_buffer.containerByteSize());

    byteSet<T> random_buffer;
    if( retval > 0 )
        random_buffer = aligned_random_buffer;
    return random_buffer;
}

template<ByteSetViewFormat const & f, typename T>
Integer byteSetView<f, T>::strToInteger(const string& val) const 
{
    uint64_t i_start = 0;
    Integer retval = 0;
    if(val.size() >= f.Header.size() && val.substr(0, f.Header.size()) == f.Header)
        i_start = f.Header.size();
    for(uint64_t i=i_start;i<val.size();i++)
        retval += this->charToDigit(val[i]) * Givaro::pow(f.Base, (val.size()-1-i));
    return retval;
}

template<ByteSetViewFormat const & f, typename T>
string byteSetView<f, T>::integerToStr(const Integer& val, const ByteSetViewFormat& format) const
{
    stringstream ss;
    string str_out;
    if(format.Base == 16)
        ss << setfill('0') << setw(this->containerBitSize()/format.BitsPerChar) << hex << val;
    else if(format.Base == 10)
        ss << dec << val;
    else if(format.Base == 2) {
        string str_val;
        byteSet<T> bs_val = ValueVector<byteSet, T>(*this);
        Integer val = Integer(bs_val);
        Integer char_mask = Givaro::pow(Integer(2), format.BitsPerChar) - 1;
        div_t d = div(bs_val.containerBitSize(), format.BitsPerChar);
        for(uint64_t i=0;i<d.quot;i++) {
            str_val = digitToChar(val & char_mask) + str_val;
            val >>= format.BitsPerChar;
        }
        if(d.rem)
            str_val = digitToChar(val & char_mask) + str_val;
        ss << str_val;
    }
    if( format.EXP ) {
        string str_wei = ss.str();
        while(str_wei.size() <= format.EXP)
            str_wei = "0" + str_wei;
        ss.str(string());
        ss << str_wei.substr(0, str_wei.size() - format.EXP) + "." + str_wei.substr(str_wei.size() - format.EXP, format.EXP);
    }
    return format.Header + ss.str();
}

template<ByteSetViewFormat const & f, typename T>
uint8_t byteSetView<f, T>::charToDigit(const char &c) const
{
    uint8_t d = 0;
    if (c >= '0' && c <= '9')
        d = c - 48;
    else if (c >= 'a' && c <= 'f')
        d = c - 87;
    else if (c >= 'A' && c <= 'F')
        d = c - 55;
    return d;
}

template<ByteSetViewFormat const & f, typename T>
char byteSetView<f, T>::digitToChar(const uint8_t &d, bool upper_case) const
{
    char c = 0;
    if (d >= 0 && d <= 9)
        c = 48 + d;
    else if (d >= 0xA && d <= 0xF)
        c = (upper_case ? 55 : 87) + d;
    return c;
}
