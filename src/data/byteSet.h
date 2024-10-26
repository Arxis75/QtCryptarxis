#pragma once

#include <data/System.h>

template <class Derived, typename T = uint8_t> 
class ValueVector
{
        //explicit ValueVector(uint64_t val, uint64_t nb_elem = 0) = delete;
        explicit ValueVector(Integer val, uint64_t nb_elem = 0) = delete;
        explicit ValueVector(const string& val, uint64_t aligned_size = 0) = delete;
    public:
        ValueVector() { vvalue.reserve(32); }
        explicit ValueVector(uint64_t nb_elem) { vvalue.resize(nb_elem); }
        ValueVector(uint8_t* p, uint64_t aligned_size);
        
        inline bool operator==(const ValueVector &v) const { return vvalue == v.vvalue; }
        inline bool operator!=(const ValueVector &v) const { return vvalue != v.vvalue; }
        inline operator uint8_t*() { return reinterpret_cast<uint8_t*>(vvalue.data()); }
        inline operator const unsigned char*() const { return reinterpret_cast<const unsigned char*>(vvalue.data()); }
        
        inline void push_front(T elem) { push_front((Derived)vector<T>({elem})); }
        inline void push_back(T elem) { vvalue.push_back(elem); }
        inline T pop_front();
        inline T pop_back();

        inline void push_front(const Derived& subset) { vvalue.insert(vvalue.begin(), subset.vvalue.begin(), subset.vvalue.end()); }
        inline void push_back(const Derived& subset) { vvalue.insert(vvalue.end(), subset.vvalue.begin(), subset.vvalue.end()); }
        Derived pop_front(uint64_t nb_element);
        Derived pop_back(uint64_t nb_element);

        inline uint64_t nbElements() const { return vvalue.size(); }
        inline uint8_t elementBitSize() const { return typeid(T) == typeid(bool) ? 1 : sizeof(T)<<3; }
        inline uint64_t containerBitSize() const { return nbElements()*elementBitSize(); }

        inline T getElem(uint64_t ofs) const { return vvalue[ofs]; }

        //inline T left(uint64_t nb_element) const { T ret_v(T(*this)); return ret_v.pop_front(nb_element); }
        //inline T right(uint64_t nb_element) const { T ret_v(T(*this)); return ret_v.pop_back(nb_element); }

    protected:
        vector<T> vvalue;   //Cf partial specialization
};

template <typename T = uint8_t> 
class byteSet : public ValueVector<byteSet<T>, T>
{
        //byteSet(uint8_t* p, uint64_t aligned_size) = delete;
        explicit byteSet(const string& val, uint64_t nb_elem = 0) = delete;
    public:
        byteSet() : ValueVector<byteSet<T>, T>() {}
        explicit byteSet(const Integer &val, uint64_t nb_elem = 0);
        explicit byteSet(const uint64_t val, uint64_t nb_elem = 0) : byteSet((Integer)val, nb_elem) {}
        byteSet(const ValueVector<byteSet<T>, T> &val) : ValueVector<byteSet<T>, T>(val) {}

        inline operator uint64_t() const { return toInteger(64); }
        inline operator Integer() const { return toInteger(this->containerBitSize()); }
        inline bool operator==(const byteSet &b) const { return Integer(*this) == Integer(b); };
        inline bool operator!=(const byteSet &b) const { return Integer(*this) != Integer(b); };

        inline uint64_t getValueNbElem(Integer val) const { return ceil(logtwo(1+val)/this->elementBitSize()); }

        inline virtual operator string() const { return Integer(*this); }

    private:
        Integer toInteger(uint64_t nb_right_bits) const;
};

struct ByteSetViewFormat { string Header; uint8_t Base; uint8_t BitsPerChar; regex Regex; };

static ByteSetViewFormat Hex  { .Header = "0x", .Base = 16, .BitsPerChar = 8, .Regex = regex("^(0x)?[0-9a-fA-F]+")};
static ByteSetViewFormat Dec  { .Header = "",   .Base = 10, .BitsPerChar = 0, .Regex = regex("^[0-9]+")};
static ByteSetViewFormat Wei = Dec;
static ByteSetViewFormat GWei { .Header = "",   .Base = 10, .BitsPerChar = 0, .Regex = regex("^[0-9]+.[0-9]{9}")};
static ByteSetViewFormat Bin  { .Header = "0b", .Base = 2,  .BitsPerChar = 1, .Regex = regex("^(0b)?[0-1]+")};

template <ByteSetViewFormat const & f = Hex, typename T = uint8_t> 
class byteSetView : public byteSet<T>
{       //explicit byteSetView(const uint64_t val, uint64_t nb_elem = 0) = delete;
    public:
        byteSetView() : byteSet<T>() {}
        explicit byteSetView(const string& val, uint64_t aligned_size = 0);
        explicit byteSetView(uint64_t val, uint64_t nb_elem = 0) : byteSet<T>(val, nb_elem) {}
        byteSetView(const byteSet<T> &val) : byteSet<T>(val) {}
        byteSetView(const ValueVector<byteSet<T>, T> &val) : byteSetView(byteSet<T>(val)) {}

        inline virtual operator string() const { return toString(f); }

        inline uint64_t getStringNbElem(string val) const { return val.size() * f.BitsPerChar / this->elemcontainerBitSize(); }
        
        uint8_t charToValue(const char &c) const;
        Integer strToInteger(const string& val) const;

    private:
        string toString(const ByteSetViewFormat& format) const { return string(""); }
};

/*********************************************** CONSTRUCTORS ***************************************************** */

template <class Derived, typename T>
ValueVector<Derived, T>::ValueVector(uint8_t* p, uint64_t aligned_size)
{
    vvalue.resize(aligned_size);
    for(uint64_t i=0;i<aligned_size;i++)
        vvalue[i] = p[i];
}

template<typename T>
byteSet<T>::byteSet(const Integer &val, uint64_t nb_elem)
    : ValueVector<byteSet<T>, T>()
{
    Integer T_mask = T(Givaro::pow(2, this->elementBitSize()) - 1);
    uint64_t nb_elem_for_val = this->getValueNbElem(val);
    uint64_t nb_extra_elem = (nb_elem > nb_elem_for_val ? nb_elem - nb_elem_for_val : 0);
    for(uint64_t i=0;i<nb_extra_elem;i++)
        this->push_back(T(0x00));
    for(uint64_t i=0;i<nb_elem_for_val;i++) {
        T toto = T(val>>((nb_elem_for_val-1-i)*this->elementBitSize()));
        this->push_back(T(T_mask & val>>((nb_elem_for_val-1-i)*this->elementBitSize())));
    }
}

template<ByteSetViewFormat const & f, typename T>
byteSetView<f, T>::byteSetView(const string& val, uint64_t nb_elem)
    : byteSet<T>()
{
    if( regex_match(val, f.Regex) ) {
        Integer i = strToInteger(val);
        this->push_back(byteSet<T>(i, nb_elem));
    }
}

/*********************************************** METHODS ***************************************************** */

template<class Derived, typename T>
Derived ValueVector<Derived, T>::pop_front(uint64_t nb_element) {
    Derived ret_value;
    assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_back(pop_front());
    return ret_value;
}

template<class Derived, typename T>
Derived ValueVector<Derived, T>::pop_back(uint64_t nb_element) {
    Derived ret_value;
    assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_front(pop_back());
    return ret_value;
}

template<class Derived, typename T>
T ValueVector<Derived, T>::pop_front()
{
    assert(nbElements());
    T ret_value = vvalue[0];
    vvalue.erase(vvalue.begin());
    return ret_value;
}

template<class Derived, typename T>
T ValueVector<Derived, T>::pop_back()
{
    assert(nbElements());
    T ret_val = vvalue[nbElements()-1];
    vvalue.pop_back();
    return ret_val;
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

template<ByteSetViewFormat const & f, typename T>
Integer byteSetView<f, T>::strToInteger(const string& val) const 
{
    uint64_t i_start = 0;
    Integer retval = 0;
    if(val.size() >= f.Header.size() && val.substr(0, f.Header.size()) == f.Header)
        i_start = f.Header.size();
    for(uint64_t i=i_start;i<val.size();i++)
        retval += this->charToValue(val[i]) * Givaro::pow(f.Base, (val.size()-1-i));
    return retval;
}

template<ByteSetViewFormat const & f, typename T>
uint8_t byteSetView<f, T>::charToValue(const char &c) const
{
    uint8_t retval = 0;
    if (c >= '0' && c <= '9')
        retval = c - 48;
    else if (c >= 'a' && c <= 'f')
        retval = c - 87;
    else if (c >= 'A' && c <= 'F')
        retval = c - 55;
    return retval;
}