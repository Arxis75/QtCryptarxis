#pragma once

#include <data/System.h>

template <class Derived, typename T = uint8_t> 
class ValueVector
{
        explicit ValueVector(uint64_t val, uint64_t nb_elem = 0) = delete;
        explicit ValueVector(Integer val, uint64_t nb_elem = 0) = delete;
        explicit ValueVector(const string& val, uint64_t aligned_size = 0) = delete;
    public:
        ValueVector() { vvalue.reserve(32); }
        explicit ValueVector(uint64_t nb_elem = 0);
        ValueVector(uint8_t* p, uint64_t aligned_size);

        inline operator uint8_t*() { return reinterpret_cast<uint8_t*>(vvalue.data()); }
        inline operator const unsigned char*() const { return reinterpret_cast<const unsigned char*>(vvalue.data()); }
        
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
        //inline uint64_t valueBitSize() const { return nbElements()*elemValueBitSize(); }

        //inline T getElem(uint64_t ofs) const { return vvalue[ofs]; }

        //inline T left(uint64_t nb_element) const { T ret_v(T(*this)); return ret_v.pop_front(nb_element); }
        //inline T right(uint64_t nb_element) const { T ret_v(T(*this)); return ret_v.pop_back(nb_element); }

    protected:
        vector<T> vvalue;   //Cf partial specialization
};

template<class Derived> class ValueVector<Derived, bool>
{
    public:
        explicit ValueVector(uint64_t nb_elem = 0) { vvalue.resize(nb_elem); }
        ValueVector(uint8_t* p, uint64_t aligned_size) {
            vvalue.resize(aligned_size);
            for(uint64_t i=0;i<aligned_size;i++)
            vvalue[i] = p[i];
        }
        inline void push_back(bool elem) { vvalue.push_back(elem); }
        inline uint8_t elemValueBitSize() const { return 1; } 
    protected:
        vector<bool> vvalue;
};
template<class Derived> class ValueVector<Derived, uint8_t>
{
    public:
        explicit ValueVector(uint64_t nb_elem = 0) { vvalue.resize(nb_elem); }
        ValueVector(uint8_t* p, uint64_t aligned_size) {
            vvalue.resize(aligned_size);
            for(uint64_t i=0;i<aligned_size;i++)
            vvalue[i] = p[i];
        }
        inline void push_back(uint8_t elem) { vvalue.push_back(elem); }
        inline uint8_t elemValueBitSize() const { return 8; }
    protected:
        vector<uint8_t> vvalue;
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
        inline operator Integer() const { return toInteger(this->valueBitSize()); }

        inline uint64_t getValueNbElem(Integer val) const { return ceil(logtwo(1+val)/this->elemValueBitSize()); }

    private:
        Integer toInteger(uint64_t nb_right_bits) const;
};

template<typename T>
byteSet<T>::byteSet(const Integer &val, uint64_t nb_elem)
    : ValueVector<byteSet<T>, T>()
{
    uint64_t nb_elem_for_val = this->getValueNbElem(val);
    uint64_t nb_extra_elem = (nb_elem > nb_elem_for_val ? nb_elem - nb_elem_for_val : 0);
    for(uint64_t i=0;i<nb_extra_elem;i++)
        this->push_back((T) 0x00);
    for(uint64_t i=nb_extra_elem;i<(nb_extra_elem + nb_elem_for_val);i++)
        this->push_back((T) 0xFF & uint8_t(val>>((nb_elem_for_val-1-i)*this->elemValueBitSize())));
}

struct ByteSetViewFormat { string Header; uint8_t BitsPerChar; regex Regex; };

static ByteSetViewFormat Hex  { .Header = "0x", .BitsPerChar = 8, .Regex = regex("^(0x)?[0-9a-fA-F]+")};
static ByteSetViewFormat Dec  { .Header = "",   .BitsPerChar = 0, .Regex = regex("^[0-9]+")};
static ByteSetViewFormat Wei = Dec;
static ByteSetViewFormat GWei { .Header = "",   .BitsPerChar = 0, .Regex = regex("^[0-9]+.[0-9]{9}")};
static ByteSetViewFormat Bin  { .Header = "0b", .BitsPerChar = 1, .Regex = regex("^(0b)?[0-1]+")};

template <typename T = uint8_t, ByteSetViewFormat const & f = Hex> 
class byteSetView : public byteSet<T>
{       //explicit byteSetView(const uint64_t val, uint64_t nb_elem = 0) = delete;
    public:
        byteSetView() : byteSet<T>() {}
        explicit byteSetView(const string& val, uint64_t aligned_size = 0) : byteSet<T>() {}
        explicit byteSetView(uint64_t val, uint64_t nb_elem = 0) : byteSet<T>(val, nb_elem) {}
        byteSetView(const byteSet<T> &val) : byteSet<T>(val) {}
        byteSetView(const ValueVector<byteSet<T>, T> &val) : byteSetView(byteSet<T>(val)) {}

        operator string() const { return toString(); }
    
    private:
        string toString(const ByteSetViewFormat& format) const;
};
