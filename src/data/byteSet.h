#pragma once

#include <data/System.h>

template <class Derived, typename T = uint8_t> 
class ValueVector
{
    public:
        ValueVector() {}
        explicit ValueVector(uint64_t nb_elem) { vvalue.resize(nb_elem); }

        inline void push_front(T elem) { push_front((Derived)vector<T>({elem})); }
        inline void push_back(T elem);  //Cf partial specialization
        inline T pop_front();
        inline T pop_back();

        inline void push_front(const Derived& subset) { vvalue.insert(vvalue.begin(), subset.vvalue.begin(), subset.vvalue.end()); }
        inline void push_back(const Derived& subset) { vvalue.insert(vvalue.end(), subset.vvalue.begin(), subset.vvalue.end()); }
        Derived pop_front(uint64_t nb_element);
        Derived pop_back(uint64_t nb_element);

        uint8_t elemValueBitSize() const;   //Cf partial specialization

        inline uint64_t nbElements() const { return vvalue.size(); }
        inline uint64_t valueBitSize() const { return nbElements()*elemValueBitSize(); }

        inline T getElem(uint64_t ofs) const { return vvalue[ofs]; }
        inline uint64_t getNbElem(uint64_t nb_bytes) const; //Cf partial specialization

        inline T left(uint64_t nb_element) const { T ret_v(T(*this)); return ret_v.pop_front(nb_element); }
        inline T right(uint64_t nb_element) const { T ret_v(T(*this)); return ret_v.pop_back(nb_element); }

    protected:
        vector<T> vvalue;   //Cf partial specialization
};

template<class Derived> class ValueVector<Derived, bool>
{
    public:
        inline void push_back(bool elem) { vvalue.push_back(elem); }
        uint8_t elemValueBitSize() const { return 1; } 
        inline uint64_t getNbElem(uint64_t nb_bytes) const { return 8*nb_bytes/elemValueBitSize(); }

    protected:
        vector<bool> vvalue;
};
template<class Derived> class ValueVector<Derived, uint8_t>
{
    public:
        inline void push_back(uint8_t elem) { vvalue.push_back(elem); }
        uint8_t elemValueBitSize() const { return 8; }
        inline uint64_t getNbElem(uint64_t nb_bytes) const { return 8*nb_bytes/elemValueBitSize(); }

    protected:
        vector<uint8_t> vvalue;
};

class ArrayVector : public ValueVector<ArrayVector, uint8_t>
{
        explicit ArrayVector(uint64_t val, uint64_t aligned_size = 0) = delete;
    public:
        ArrayVector() : ValueVector() {}
        ArrayVector(uint8_t* p, uint64_t aligned_size);
        explicit ArrayVector(const ValueVector &val) : ValueVector(val) {}

        inline operator uint8_t*() { return reinterpret_cast<uint8_t*>(vvalue.data()); }
        inline operator const unsigned char*() const { return reinterpret_cast<const unsigned char*>(vvalue.data()); }
};

template <typename T = uint8_t> 
class byteSet : public ValueVector<byteSet<T>, T>
{
        explicit byteSet(const string& val, uint64_t aligned_size = 0) = delete;
    public:
        byteSet() : ValueVector<byteSet<T>, T>() {}
        explicit byteSet(const Integer &val, uint64_t aligned_size = 0);
        explicit byteSet(const uint64_t val, uint64_t aligned_size = 0) : byteSet((Integer)val, aligned_size) {}
        byteSet(const ValueVector<byteSet<T>, T> &val) : ValueVector<byteSet<T>, T>(val) {}

        inline operator uint64_t() const { return toInteger(64); }
        inline operator Integer() const { return toInteger(this->valueBitSize()); }

private:
        Integer toInteger(uint64_t nb_right_bits) const;
};

template<typename T>
byteSet<T>::byteSet(const Integer &val, uint64_t aligned_size)
    : ValueVector<byteSet<T>, T>()
{
    uint64_t nb_elem_for_aligned_size = this->getNbElem(aligned_size);
    uint64_t nb_elem_for_val = this->getNbElem(val.size_in_base(pow(2, this->elemValueBitSize())));
    uint64_t nb_extra_elem = (nb_elem_for_aligned_size > nb_elem_for_val ? nb_elem_for_aligned_size - nb_elem_for_val : 0);
    for(uint64_t i=0;i<nb_extra_elem;i++)
        this->push_back((T) 0x00);
    for(uint64_t i=nb_extra_elem;i<(nb_extra_elem + nb_elem_for_val);i++)
        this->push_back((T) 0xFF & uint8_t(val>>((nb_elem_for_val-1-i)*this->elemValueBitSize())));
}

template <typename T = uint8_t> 
class byteSetView : public byteSet<T>
{   
    struct ByteSetViewFormat { string Header; uint8_t BitsPerChar; regex Regex; };
    
    static ByteSetViewFormat Hex  { .Header = "0x", .BitsPerChar = 8, .Regex = regex("^(0x)?[0-9a-fA-F]+")};
    static ByteSetViewFormat Dec  { .Header = "",   .BitsPerChar = 0, .Regex = regex("^[0-9]+")};
    static ByteSetViewFormat Wei = Dec;
    static ByteSetViewFormat GWei { .Header = "",   .BitsPerChar = 0, .Regex = regex("^[0-9]+.[0-9]{9}")};
    static ByteSetViewFormat Bin  { .Header = "0b", .BitsPerChar = 1, .Regex = regex("^(0b)?[0-1]+")};

    public:
        byteSetView() : byteSet<T>(), m_format(Hex) {}
        explicit byteSetView(const ByteSetViewFormat& format, const string& val, uint64_t aligned_size = 0) : byteSet<T>(), m_format(format) {}
        explicit byteSetView(uint64_t val, uint64_t aligned_size = 0) : byteSet<T>(val, aligned_size), m_format(Hex) {}
        explicit byteSetView(const byteSet<T> &val) : byteSet<T>(val), m_format(Hex) {}

        operator string() const { return toString(m_format); }
    
    private:
        string toString(const ByteSetViewFormat& format) const;

    private:
        ByteSetViewFormat m_format;
};
