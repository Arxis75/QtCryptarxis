#pragma once

#include <data/System.h>

template <class Derived, typename T = uint8_t> 
class ValueVector
{
    public:
        ValueVector() {}
        explicit ValueVector(uint64_t nb_elem) { vvalue.resize(nb_elem); }

        inline void push_front(T elem) { push_front((Derived)vector<T>({elem})); }
        inline void push_back(T elem) { vvalue.push_back(elem); }
        T pop_front();
        T pop_back();

        inline void push_front(const Derived& subset) { vvalue.insert(vvalue.begin(), subset.vvalue.begin(), subset.vvalue.end()); }
        inline void push_back(const Derived& subset) { vvalue.insert(vvalue.end(), subset.vvalue.begin(), subset.vvalue.end()); }
        Derived pop_front(uint64_t nb_element);
        Derived pop_back(uint64_t nb_element);

        inline uint64_t elemSize() const { return vvalue.size(); }

        uint8_t getElemBitSize() const;

        T getElem(uint64_t ofs) const { return vvalue[ofs]; }

    protected:
        vector<T> vvalue;
};

class ArrayVector : public ValueVector<ArrayVector, uint8_t>
{
        explicit ArrayVector(uint64_t val, uint64_t aligned_size = 0) = delete;
    public:
        ArrayVector() : ValueVector() {}
        ArrayVector(uint8_t*, uint64_t) : ValueVector() {}
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
        explicit byteSet(const Integer &val, uint64_t aligned_size = 0) : ValueVector<byteSet<T>, T>() {}
        explicit byteSet(uint64_t val, uint64_t aligned_size = 0) : ValueVector<byteSet<T>, T>() {}
        byteSet(const ValueVector<byteSet<T>, T> &val) : ValueVector<byteSet<T>, T>(val) {}
    
        inline operator uint64_t() const { return right(); }
        inline operator Integer() const { return right(elemSize()); }
    
    private:
        Integer right(uint64_t byte_size) const;
};

template <typename T = uint8_t> 
class byteSetView : public byteSet<T>
{
    public:
        byteSetView() : byteSet<T>() {}
        explicit byteSetView(const string& val, uint64_t aligned_size = 0) : byteSet<T>() {}
        explicit byteSetView(uint64_t val, uint64_t aligned_size = 0) : byteSet<T>(val, aligned_size) {}
        explicit byteSetView(const byteSet<T> &val) : byteSet<T>(val) {}

        operator string() const {}
};