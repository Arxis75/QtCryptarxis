#pragma once

#include <data/System.h>
#include <crypto/System.h>

template <typename T> class ByteSet;

template <template <typename T> class Derived = ByteSet, typename T = uint8_t>
class RawByteSet
{
        template<typename U, std::enable_if_t<std::is_integral<U>::value, bool> = true>
            explicit RawByteSet(const U& val, uint64_t nb_elem = 0) = delete;
        template<typename U, std::enable_if_t<std::is_same<U, Integer>::value ,bool> = true>
            explicit RawByteSet(const U& val, uint64_t nb_elem = 0) = delete;

        RawByteSet(const string& p, uint64_t aligned_size) = delete;
        RawByteSet(const char* p, uint64_t aligned_size) = delete;
    public:
        /// @brief Template Friendship for copy-constructor to be able to access protected members
        template<template <typename> class, typename> friend class RawByteSet;

        //Default Constructors
        RawByteSet() { vvalue.reserve(isAligned() ? 32 : 256); }
        //Copy Constructor
        template<template <typename> class D, typename U>
            RawByteSet(const RawByteSet<D, U>& v); 
        //Array-Copy Constructors
        template <typename U> 
            RawByteSet(const U *p, uint64_t aligned_size);   // const U* = const uint8_t*, const unsigned char*
        template <typename U> 
            explicit RawByteSet(const U *str);               // const U = const char*
            
        //Const& and Const* Operators/Accessors
        inline const uint8_t& operator[](uint64_t elem_index) const { return vvalue[elem_index]; };
        /// @brief For convenience only, at(...) is friendlier than (*this)[...]
        inline const uint8_t& at(uint64_t elem_index) const { return (*this)[elem_index]; };
        inline operator const unsigned char*() const { assert(isAligned()); return reinterpret_cast<const unsigned char*>(vvalue.data()); }

        //Non-const Operators/Accessors
        inline operator uint8_t*() { assert(isAligned()); return reinterpret_cast<uint8_t*>(vvalue.data()); }

        //Const Operators/Accessors
        inline bool operator==(const RawByteSet &v) const { return vvalue == v.vvalue; }
        inline bool operator!=(const RawByteSet &v) const { return vvalue != v.vvalue; }
        virtual operator string() const;
        /// @brief Gets the size in bits of the stored value.
        /// @return The logical size in  bits of the container, not the vector size.
        inline uint64_t bitSize() const { return nbElements()*elementBitSize(); }
        /// @brief Gets the size in bytes of the stored value (rounded to the upper byte if T=bool).
        /// @return The logical size in  bytes of the container, not the vector size.
        inline uint64_t byteSize() const { return (bitSize() >> 3) + (bitSize()%8 ? 1 : 0); }
        inline T getElem(uint64_t elem_index) const { return T(vvalue[elem_index]); };
        Derived<T> get(uint64_t elem_offset, const uint64_t nb_element) const;
        inline Derived<T> left(uint64_t nb_element) const { return get(0, nb_element); }
        inline Derived<T> right(uint64_t nb_element) const { return get(nbElements() - nb_element, nb_element); }
        inline Derived<uint8_t> sha256() const;
        inline Derived<uint8_t> keccak256() const;

        //Container manipulation interface
        inline void resize(uint64_t nb_elem) { vvalue.resize(nb_elem); }
        inline void clear() { vvalue.clear(); }

        inline void push_front(T elem) { vvalue.insert(vvalue.begin(), elem); }
        inline void push_back(T elem) { vvalue.push_back(elem); }
        inline T pop_front();
        inline T pop_back();

        inline void push_front(const Derived<T>& subset) { vvalue.insert(vvalue.begin(), subset.vvalue.begin(), subset.vvalue.end()); }
        inline void push_back(const Derived<T>& subset) { vvalue.insert(vvalue.end(), subset.vvalue.begin(), subset.vvalue.end()); }
        Derived<T> pop_front(uint64_t nb_element);
        Derived<T> pop_back(uint64_t nb_element);

        inline void push_front(const char* str) { push_front(RawByteSet<Derived, T>(str)); }
        inline void push_back(const char* str) { push_back(RawByteSet<Derived, T>(str)); }

        //ostream
        friend inline ostream& operator<<(ostream& out, const RawByteSet& v) { return out << string(v); }

        /// @brief Constructor for testing purposes
        void fromV(const vector<uint8_t>& v) { vvalue = v; }
        const vector<uint8_t>& toV() const { return vvalue; }

    protected:
        //Const accessors
        inline bool getBit(uint64_t bit_offset) const { return (1 << (bit_offset % elementBitSize())) & vvalue[(bitSize() - 1 - bit_offset) / elementBitSize()]; }

        //Container manipulation interface
        inline void setBit(uint64_t bit_offset, const bool& bit_value) { bit_value == 0 ? setBit0(bit_offset) : setBit1(bit_offset); }
        inline void setBit0(uint64_t bit_offset) { vvalue[(bitSize() - 1 - bit_offset) / elementBitSize()] &= ~(1 << (bit_offset % elementBitSize())); }
        inline void setBit1(uint64_t bit_offset) { vvalue[(bitSize() - 1 - bit_offset) / elementBitSize()] |= (1 << (bit_offset % elementBitSize())); }
        inline void setElem(uint64_t elem_offset, const T& elem) { vvalue[elem_offset] = elem; }

        //Property accessors
        inline bool isAligned() const { return typeid(T) == typeid(uint8_t); }
        inline uint64_t nbElements() const { return vvalue.size(); }
        inline uint64_t bytesToNbElements(uint64_t bytes) const { return ((bytes << 3) / elementBitSize()); }
        inline uint8_t elementBitSize() const { return isAligned() ? 8 : 1; }
        
    private:
        vector<uint8_t> vvalue;
};

struct StrByteSetFormat { string Header; uint8_t Base; uint8_t BitsPerChar; regex Regex; bool UpperCase; uint8_t EXP; };

template <StrByteSetFormat const & f, typename T> class StrByteSet;

template <typename T = uint8_t> 
class ByteSet : public RawByteSet<ByteSet, T>
{
        explicit ByteSet(uint8_t* val, uint64_t nb_elem) = delete;
        explicit ByteSet(const unsigned char* val, uint64_t nb_elem) = delete;

        explicit ByteSet(const string& val, uint64_t nb_elem = 0) = delete;
        explicit ByteSet(const char* val, uint64_t nb_elem = 0) = delete;
    public:
        //Default constructor
        ByteSet() : RawByteSet<ByteSet, T>() {}
        //Copy Constructors
        template<StrByteSetFormat const & f, typename U>
            ByteSet(const StrByteSet<f, U> &val) : RawByteSet<ByteSet, T>(val) {}   //FIXME: should not be necessary
        template<typename U>
            ByteSet(const ByteSet<U>& b) : RawByteSet<ByteSet, T>(b) {}
        template<typename U>
            ByteSet(const RawByteSet<ByteSet, U> &val) : RawByteSet<ByteSet, T>(val) {}
        //Constructor from integral and bool values
        template<typename U>
            explicit ByteSet(const U &val, uint64_t nb_elem = 0);   // U = integral and bool values

        inline operator uint64_t() const { return (uint64_t)toInteger(); }
        inline operator Integer() const { return toInteger(); }
        inline bool operator==(const ByteSet &b) const { return this->bitSize() == b.bitSize() && Integer(*this) == Integer(b); };
        inline bool operator!=(const ByteSet &b) const { return !((*this) == b); };

        inline void push_front(const Integer& val, uint64_t nb_elem) { RawByteSet<ByteSet, T>::push_front((RawByteSet<ByteSet, T>)ByteSet(val, nb_elem)); }
        inline void push_back(const Integer& val, uint64_t nb_elem) { RawByteSet<ByteSet, T>::push_back((RawByteSet<ByteSet, T>)ByteSet(val, nb_elem)); }

        static ByteSet<T> generateRandom(uint64_t nb_element);

    protected:
       // Integer parsing
        inline uint64_t getValueNbElem(Integer val) const { return ceil(logtwo(1+val)/this->elementBitSize()); }
        inline T getValueElem(const Integer &val, uint64_t elem_offset) const { return T((Givaro::pow(2,this->elementBitSize())-1) & (val >> (getValueNbElem(val) - 1 - elem_offset) * (this->elementBitSize()))); }

        Integer toInteger() const;
};

static StrByteSetFormat Hex  { .Header = "0x", .Base = 16, .BitsPerChar = 4, .Regex = regex("^(0x)?[0-9a-fA-F]+"), .UpperCase = false, .EXP = 0};
static StrByteSetFormat Dec  { .Header = "",   .Base = 10, .BitsPerChar = 0, .Regex = regex("^[0-9]+"),            .UpperCase = false, .EXP = 0};
static StrByteSetFormat Wei = Dec;
static StrByteSetFormat GWei { .Header = "",   .Base = 10, .BitsPerChar = 0, .Regex = regex("^[0-9]+.[0-9]{9}"),   .UpperCase = false, .EXP = 9};
static StrByteSetFormat Bin  { .Header = "0b", .Base = 2,  .BitsPerChar = 1, .Regex = regex("^(0b)?[0-1]+"),       .UpperCase = false, .EXP = 0};

template <StrByteSetFormat const & f = Hex, typename T = uint8_t> 
class StrByteSet : public ByteSet<T>
{
        explicit StrByteSet(uint8_t* val, uint64_t nb_elem) = delete;
        explicit StrByteSet(const unsigned char* val, uint64_t nb_elem) = delete;

        template<typename U, std::enable_if_t<std::is_integral<U>::value, bool> = true>
            explicit StrByteSet(const U& val, uint64_t nb_elem = 0) = delete;
        template<typename U, std::enable_if_t<std::is_same<U, Integer>::value ,bool> = true>
            explicit StrByteSet(const U& val, uint64_t nb_elem = 0) = delete;
    public:
        //Default constructor
        StrByteSet() : ByteSet<T>() {}
        //Copy Constructors
        template<StrByteSetFormat const & g, typename U>
            StrByteSet(const StrByteSet<g, U>& b) : ByteSet<T>(b) {}
        template<typename U>
            StrByteSet(const ByteSet<U> &val) : ByteSet<T>(val) {}
        template<typename U>
            StrByteSet(const RawByteSet<ByteSet, U> &val) : ByteSet<T>(val) {}
        //Constructor from strings
        template<typename U>
            explicit StrByteSet(const U&, uint64_t aligned_size = 0);     // U = const string&
        template<typename U>
            explicit StrByteSet(const U*, uint64_t aligned_size = 0);     // U = const char*

        inline virtual operator string() const { return toFormat(f); }

        inline void push_front(const string& str, uint64_t nb_elem = 0) { RawByteSet<ByteSet, T>::push_front(StrByteSet(str, nb_elem)); }
        inline void push_back(const string& str, uint64_t nb_elem = 0) { RawByteSet<ByteSet, T>::push_back(StrByteSet(str, nb_elem)); }

        inline string toFormat(const StrByteSetFormat& format) const { return integerToStr(Integer(*this), format); }

    protected:

        bool isFormatAligned() const { return f.Base == 16 || f.Base == 2; }

        //String Parsing
        inline uint64_t getStringNbElem(string val) const 
        {
            assert(isFormatAligned());
            uint64_t x = (val.size() * f.BitsPerChar / this->elementBitSize()) + ((val.size() * f.BitsPerChar)%(this->elementBitSize()) ? ceil(float(f.BitsPerChar)/this->elementBitSize()) : 0);
            return x;
        }

        Integer strToInteger(const string& val) const;
        string integerToStr(const Integer& val, const StrByteSetFormat& format = f) const;

        string removeCharsFromString(const string &val, const char* charsToRemove) const;
        string toInternalFormat(const string& val) const;

        uint8_t charToDigit(const char &c) const;
        char digitToChar(const uint8_t &n, bool upper_case = f.UpperCase) const;
};

/*********************************************** CONSTRUCTORS ***************************************************** */

template <template <typename> class Derived, typename T>
template<template <typename> class D, typename U>
RawByteSet<Derived, T>::RawByteSet(const RawByteSet<D, U>& v)
{
    if(isAligned() == v.isAligned())
        //Same alignment
        vvalue = v.vvalue;
    else {
        // Different alignment => Byte-alignment via byteSize()
        vvalue.resize((v.byteSize() << 3) / elementBitSize());
        for(uint64_t i = 0 ; i < v.bitSize() ; i++)
            // bit per bit copy
            setBit(i, v.getBit(i));
    }
}

template <template <typename> class Derived, typename T>
template <typename U>
RawByteSet<Derived, T>::RawByteSet(const U* p, uint64_t aligned_size)
{
    static_assert( std::is_same<std::decay_t<U>, uint8_t>::value || std::is_same<std::decay_t<U>, unsigned char>::value, "Constructor accepts only <T=uint8_t>, const uint8_t*, const unsigned char*");

    RawByteSet<Derived, uint8_t> aligned_me;
    for(uint64_t i=0;i<aligned_size;i++) 
        aligned_me.push_back(p[i]);
    resize(aligned_me.bitSize() / elementBitSize());
    *this = aligned_me;
}

template <template <typename> class Derived, typename T>
template <typename U>
RawByteSet<Derived, T>::RawByteSet(const U* str)
    : RawByteSet(reinterpret_cast<const uint8_t*>(str), strlen(str))
{
    static_assert( std::is_same<std::decay_t<U>, char>::value, "Constructor accepts only <T=uint8_t>, const char*");
}

template<typename T>
template<typename U>
ByteSet<T>::ByteSet(const U &val, uint64_t nb_elem)
    : RawByteSet<ByteSet, T>()
{
    static_assert(std::is_integral<U>::value || std::is_integral<bool>::value, "Constructor accepts only integral values");

    uint64_t nb_elem_for_val = this->getValueNbElem(val);
    uint64_t i_extra = (nb_elem > nb_elem_for_val ? nb_elem - nb_elem_for_val : 0);
    for(uint64_t i=0;i<i_extra;i++)
        RawByteSet<ByteSet, T>::push_back(T(0x00));
    uint64_t i_start = (nb_elem ? (nb_elem < nb_elem_for_val ? nb_elem_for_val - nb_elem : 0) : 0);
    for(uint64_t i=i_start;i<nb_elem_for_val;i++)
        RawByteSet<ByteSet, T>::push_back(this->getValueElem(val, i));
}

template<StrByteSetFormat const & f, typename T>
template<typename U>
StrByteSet<f, T>::StrByteSet(const U& val, uint64_t nb_elem)
    : ByteSet<T>()
{
    static_assert(std::is_same<std::decay_t<U>, string>::value, "Constructor accepts only const string&");

    if( regex_match(val, f.Regex) ) {
        string str = toInternalFormat(val);
        *this = ByteSet<T>(strToInteger(str), (nb_elem ? nb_elem : (isFormatAligned() ? getStringNbElem(str) : 0)));
    }
}

template<StrByteSetFormat const & f, typename T>
template<typename U>
StrByteSet<f, T>::StrByteSet(const U* val, uint64_t nb_elem)
    : StrByteSet((string)val, nb_elem)
{
    static_assert(std::is_same<std::decay_t<U>, char>::value, "Constructor accepts only const char*");
}

/*********************************************** METHODS ***************************************************** */

template <template <typename> class Derived, typename T>
Derived<T> RawByteSet<Derived, T>::get(uint64_t elem_offset, const uint64_t nb_element) const
{
    assert(nbElements() >= elem_offset + nb_element);
    Derived<T> ret_value;
    ret_value.pop_back(nbElements() - (elem_offset + nb_element));
    return ret_value;
}

template <template <typename> class Derived, typename T>
Derived<T> RawByteSet<Derived, T>::pop_front(uint64_t nb_element) {
    Derived<T> ret_value;
    //assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.RawByteSet<ByteSet, T>::push_back(pop_front());
    return ret_value;
}

template <template <typename> class Derived, typename T>
Derived<T> RawByteSet<Derived, T>::pop_back(uint64_t nb_element) {
    Derived<T> ret_value;
    //FIXME incompatible with tests ... 
    //assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.RawByteSet<ByteSet, T>::push_front(pop_back());
    return ret_value;
}

template <template <typename> class Derived, typename T>
T RawByteSet<Derived, T>::pop_front()
{
    assert(nbElements());
    uint8_t ret_value = vvalue[0];
    vvalue.erase(vvalue.begin());
    return ret_value;
}

template <template <typename> class Derived, typename T>
T RawByteSet<Derived, T>::pop_back()
{
    assert(nbElements());
    uint8_t ret_val = vvalue[nbElements()-1];
    vvalue.pop_back();
    return ret_val;
}

template <template <typename> class Derived, typename T>
RawByteSet<Derived, T>::operator string() const
{
    stringstream ss;
    for(uint8_t i: vvalue)
        ss << setfill('0') << setw(elementBitSize()>>2) << hex << Integer(i) << ' ';
    return ss.str();
}

template <template <typename> class Derived, typename T>
Derived<uint8_t> RawByteSet<Derived, T>::sha256() const
{
    RawByteSet<Derived, uint8_t> aligned_me(*this);
    RawByteSet<Derived, uint8_t> digest;
    digest.resize(32);
    SHA256(aligned_me, aligned_me.byteSize(), digest);
    return Derived<uint8_t>(digest);
}

template <template <typename> class Derived, typename T>
Derived<uint8_t> RawByteSet<Derived, T>::keccak256() const
{
    RawByteSet<Derived, uint8_t> aligned_me(*this);
    hash256 h;
    h = ethash::keccak256(aligned_me, aligned_me.byteSize());
    return Derived<uint8_t>(RawByteSet<Derived, uint8_t>(&h.bytes[0], 32));
}

template<typename T>
Integer ByteSet<T>::toInteger() const
{
    Integer ret_value = 0;
    for(uint64_t i=0;i<this->nbElements();i++)
        ret_value += (Integer(this->getElem(this->nbElements()-1-i)) << (i*this->elementBitSize()));
    return ret_value;     
}

template<typename T>
ByteSet<T> ByteSet<T>::generateRandom(uint64_t nb_element)
{
    int retval = -1;
    RawByteSet<ByteSet, uint8_t> aligned_random_buffer;
    uint64_t nb_bytes = nb_element / (typeid(T) == typeid(bool) ? 8 : 1);
    aligned_random_buffer.resize(nb_bytes);
    retval = RAND_bytes(aligned_random_buffer, aligned_random_buffer.byteSize());

    ByteSet<T> random_buffer;
    if( retval > 0 )
        random_buffer = aligned_random_buffer;
    return random_buffer;
}

template<StrByteSetFormat const & f, typename T>
string StrByteSet<f, T>::removeCharsFromString(const string &val, const char* charsToRemove) const
{
    string str_out = val;
    for (uint8_t i = 0; i < strlen(charsToRemove); ++i ) {
        str_out.erase( remove(str_out.begin(), str_out.end(), charsToRemove[i]), str_out.end() );
    }
    return str_out;
}

template<StrByteSetFormat const & f, typename T>
string StrByteSet<f, T>::toInternalFormat(const string& val) const
{
    string ret_val = val;
    //Removes the Header
    if(val.size() >= f.Header.size() && val.substr(0, f.Header.size()) == f.Header)
        ret_val = val.substr(f.Header.size(), val.size() - f.Header.size());
    //Removes the Exponentiation
    ret_val = removeCharsFromString(ret_val.c_str(), ".");
    return ret_val;
}

template<StrByteSetFormat const & f, typename T>
Integer StrByteSet<f, T>::strToInteger(const string& val) const 
{
    uint64_t i_start = 0;
    Integer retval = 0;
    for(uint64_t i=0;i<val.size();i++)
        retval += this->charToDigit(val[i]) * Givaro::pow(f.Base, (val.size()-1-i));
    return retval;
}

template<StrByteSetFormat const & f, typename T>
string StrByteSet<f, T>::integerToStr(const Integer& val, const StrByteSetFormat& format) const
{
    stringstream ss;
    string str_out;
    if(format.Base == 16)
        ss << setfill('0') << setw(this->bitSize()/format.BitsPerChar) << hex << val;
    else if(format.Base == 10)
        ss << dec << val;
    else if(format.Base == 2) {
        string str_val;
        ByteSet<T> bs_val = RawByteSet<ByteSet, T>(*this);
        Integer val = Integer(bs_val);
        Integer char_mask = Givaro::pow(Integer(2), format.BitsPerChar) - 1;
        div_t d = div(bs_val.bitSize(), format.BitsPerChar);
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

template<StrByteSetFormat const & f, typename T>
uint8_t StrByteSet<f, T>::charToDigit(const char &c) const
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

template<StrByteSetFormat const & f, typename T>
char StrByteSet<f, T>::digitToChar(const uint8_t &d, bool upper_case) const
{
    char c = 0;
    if (d >= 0 && d <= 9)
        c = 48 + d;
    else if (d >= 0xA && d <= 0xF)
        c = (upper_case ? 55 : 87) + d;
    return c;
}
