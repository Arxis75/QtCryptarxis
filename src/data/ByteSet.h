#pragma once

#include <data/System.h>
#include <data/Tools.h>     //To improve (migrate some Tools functions into ByteSet class)

class ByteSet
{
    public:       
        ByteSet() { vvalue.reserve(32); };
        /// Copy constructor
        ByteSet(const ByteSet &b) { vvalue = b.vvalue; }

        /// Array Constructor from array of bytes
        ByteSet(const uint8_t *p, uint64_t size) { vvalue.reserve(size); push_back_ptr(p, size); }
        /// Array Constructor from array of chars interpreted as bytes
        ByteSet(const char* str) : ByteSet(reinterpret_cast<const uint8_t*>(str), strlen(str)) { }
        /// Array Constructor from vector of bytes
        explicit ByteSet(const vector<uint8_t> &v) { vvalue = v; }
        
        /// Value constructor from Integer
        /// The output ByteSet size equals the "size" parameter
        /// BEWARE: For construction from value=0, the caller must explicitely use Integer::zero or Integer(0), 
        /// else, it could lead to ByteSet(const uint8_t *p, uint64_t size) being called.
        ByteSet(const Integer& value, uint64_t size);
        /// Value constructor from Integer
        /// The output ByteSet size is the minimal size containing the value
        explicit ByteSet(const Integer& value) : ByteSet(value, sizeInBytes(value)) { }
        /// Value constructor from uint64_t
        /// The output ByteSet size is the minimal size containing the value, and NOT 8 bytes.
        explicit ByteSet(const uint64_t value) { vvalue.reserve(8); push_back(value, sizeInBytes64(value)); }

        /// For string representing a number in base 2 or 16
        /// BEWARE: don't use 1-parameter (const string &str) constructor, as it might be implicitely converted to Integer
        /// "fixed_size" is only used for adding 0x00 front padding if "fixed_size" exceeds the value size
        /// A "fixed_size" smaller than the value size does not truncate the ByteSet
        ByteSet(const string& str_value, const uint64_t size, const uint8_t in_base) { vvalue.reserve(size); push_back(str_value, size, in_base); };

        void resize(const uint32_t size, const uint8_t value = 0) { vvalue.resize(size, value); }

        void push_back(const ByteSet &b) { vvalue.insert(vvalue.end(), b.vvalue.begin(), b.vvalue.end()); }
        void push_back(const uint64_t value, const uint64_t size);
        void push_back_ptr(const uint8_t *p, const uint64_t size);
        void push_back(const string &str_value, const uint64_t size, const uint8_t in_base);

        const void push_front(const ByteSet &b) { vvalue.insert(vvalue.begin(), b.vvalue.begin(), b.vvalue.end()); };
        const void push_front(const uint64_t value, const uint64_t size);
        const ByteSet pop_front(const uint64_t size);

        const ByteSet sha256() const;
        const ByteSet keccak256() const;

        friend ostream& operator<<(ostream &out, const ByteSet &v);

        inline void clear() { vvalue.clear(); }
        inline const uint64_t byteSize() const { return vvalue.size(); }

        inline operator uint8_t*() { return reinterpret_cast<uint8_t*>(vvalue.data()); }
        inline operator const unsigned char*() const { return reinterpret_cast<const unsigned char*>(vvalue.data()); }     
        inline operator const vector<uint8_t>() const { return vvalue; }
        inline operator const Integer() const { return as_Integer(); }
        operator const string() const;  // inline in the .cpp does not compile!?!

        inline bool operator==(const ByteSet &b) const { return vvalue == b.vvalue; }
        inline bool operator!=(const ByteSet &b) const { return vvalue != b.vvalue; }
        inline bool operator< (const ByteSet &b) const { return Integer(*this) <  Integer(b); }
        inline bool operator> (const ByteSet &b) const { return Integer(*this) >  Integer(b); }
        inline bool operator<=(const ByteSet &b) const { return Integer(*this) <= Integer(b); }
        inline bool operator>=(const ByteSet &b) const { return Integer(*this) >= Integer(b); }

        inline const ByteSet at(const uint64_t offset, const uint64_t size) const { return ByteSet(&vvalue[offset], size); };
        inline const uint8_t as_uint8() const { return (byteSize()>0 ? vvalue[0] : 0); }
        const uint64_t as_uint64() const;
        const Integer as_Integer() const { return a2Integer(vvalue.data(), vvalue.size()); }
        const bool as_bool() const { return (as_uint8() ? true : false); }
        
        static const ByteSet generateRandom(const uint32_t size);

    protected:
        const Integer a2Integer(const uint8_t *input, const int32_t size) const;

    protected:
        vector<uint8_t> vvalue;
};
