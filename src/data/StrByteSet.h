#pragma once

#include <data/IntByteSet.h>

class StrByteSet : public IntByteSet
{
    public:
        StrByteSet() : IntByteSet() {}
        StrByteSet(const string &val, const string& header, const string& str_regex, bool is_aligned, uint8_t chars_per_byte, uint64_t aligned_size = 0);
        explicit StrByteSet(const ByteSet &val) : IntByteSet(val) {}

        /// @brief string operator returning the default representation
        /// @return Size in Bytes of the value represented by the hex/bin strings, 0-padding included.
        /// The dec/Gwei strings being not aligned, their size is not relevant here
        virtual operator string() const;

        inline void push_front(const string &val, uint64_t aligned_size = 0) { ByteSet::push_front(StrByteSet(val, m_header, m_regex, m_is_aligned, m_chars_per_byte, aligned_size)); }
        inline StrByteSet pop_front(uint64_t nb_element) { return StrByteSet(ByteSet::pop_front(nb_element)); }

        inline void push_back(const string &val, uint64_t aligned_size = 0) { ByteSet::push_back(StrByteSet(val, m_header, m_regex, m_is_aligned, m_chars_per_byte, aligned_size)); }
        inline StrByteSet pop_back(uint64_t nb_element) { return StrByteSet(ByteSet::pop_back(nb_element)); }

    protected:
        string removeCharsFromString(const string &val, const char* charsToRemove);
        
    private:
        virtual void construct(const string &val, uint64_t aligned_size);

        string removeBaseHeader(const string &val);
        string alignToByte(const string &val, uint64_t aligned_size) const;
        uint8_t charToNibble(const char &c) const;
        char nibbleToChar(const uint8_t &nibble) const;

    private:
        string m_header;
        string m_regex;
        uint8_t m_chars_per_byte;
        bool m_is_aligned;
};