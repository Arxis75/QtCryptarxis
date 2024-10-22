#pragma once

#include <data/IntByteSet.h>

class StrByteSet : public IntByteSet
{
    public:
        /// @brief string operator returning the default representation
        /// @return Size in Bytes of the value represented by the hex/bin strings, 0-padding included.
        /// The dec/Gwei strings being not aligned, their size is not relevant here
        virtual operator string() const;

        inline const string& getHeader() const { return m_header; }
        inline const string& getRegex() const { return m_regex; }
        inline const uint8_t& getCharsPerByte() const { return m_chars_per_byte; }
        inline const bool& getIsAligned() const { return m_is_aligned; }

    protected:
        StrByteSet() : IntByteSet() {}
        StrByteSet(const string &val, const string& header, const string& str_regex, bool is_aligned, uint8_t chars_per_byte, uint64_t aligned_size = 0);
        explicit StrByteSet(const ByteSet &val) : IntByteSet(val) {}

        virtual void construct(const string &val, uint64_t aligned_size);

        string removeCharsFromString(const string &val, const char* charsToRemove);
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

class HexStrByteSet : public StrByteSet {
    public:
        HexStrByteSet() : StrByteSet() {}
        explicit HexStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit HexStrByteSet(const ByteSet &val) : StrByteSet(val) { }

        inline void push_front(const string &val, uint64_t aligned_size = 0) { ByteSet::push_front(HexStrByteSet(val, aligned_size)); }
        inline HexStrByteSet pop_front(uint64_t nb_element) { return HexStrByteSet(ByteSet::pop_front(nb_element)); }
        inline void push_back(const string &val, uint64_t aligned_size = 0) { ByteSet::push_back(HexStrByteSet(val, aligned_size)); }
        inline HexStrByteSet pop_back(uint64_t nb_element) { return HexStrByteSet(ByteSet::pop_back(nb_element)); }
};

class BinStrByteSet : public StrByteSet {
    public:
        BinStrByteSet() : StrByteSet() {}
        explicit BinStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit BinStrByteSet(const ByteSet &val) : StrByteSet(val) { }

        inline void push_front(const string &val, uint64_t aligned_size = 0) { ByteSet::push_front(BinStrByteSet(val, aligned_size)); }
        inline BinStrByteSet pop_front(uint64_t nb_element) { return BinStrByteSet(ByteSet::pop_front(nb_element)); }
        inline void push_back(const string &val, uint64_t aligned_size = 0) { ByteSet::push_back(BinStrByteSet(val, aligned_size)); }
        inline BinStrByteSet pop_back(uint64_t nb_element) { return BinStrByteSet(ByteSet::pop_back(nb_element)); }
};

class BitStrByteSet : public StrByteSet {
    public:
        BitStrByteSet() : StrByteSet() {}
        explicit BitStrByteSet(const string &val, uint64_t nb_bits = 0);
        explicit BitStrByteSet(const ByteSet &val) : StrByteSet(val) { }

        inline void push_front(const string &val, uint64_t nb_bits = 0) { ByteSet::push_front(BitStrByteSet(val, nb_bits)); }
        inline BitStrByteSet pop_front(uint64_t nb_element) { return BitStrByteSet(ByteSet::pop_front(nb_element)); }
        inline void push_back(const string &val, uint64_t nb_bits = 0) { ByteSet::push_back(BitStrByteSet(val, nb_bits)); }
        inline BitStrByteSet pop_back(uint64_t nb_element) { return BitStrByteSet(ByteSet::pop_back(nb_element)); }

        BinStrByteSet toBinStrByteSet() const;
};

class DecStrByteSet : public StrByteSet {
    public:
        DecStrByteSet() : StrByteSet() {}
        explicit DecStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit DecStrByteSet(const ByteSet &val) : StrByteSet(val) { }

        inline void push_front(const string &val, uint64_t aligned_size = 0) { ByteSet::push_front(DecStrByteSet(val, aligned_size)); }
        inline DecStrByteSet pop_front(uint64_t nb_element) { return DecStrByteSet(ByteSet::pop_front(nb_element)); }
        inline void push_back(const string &val, uint64_t aligned_size = 0) { ByteSet::push_back(DecStrByteSet(val, aligned_size)); }
        inline DecStrByteSet pop_back(uint64_t nb_element) { return DecStrByteSet(ByteSet::pop_back(nb_element)); }

        virtual operator string() const;

    private:
        virtual void construct(const string &val, uint64_t aligned_size);
};

class GWeiStrByteSet : public StrByteSet {
    public:
        GWeiStrByteSet() : StrByteSet() {}
        explicit GWeiStrByteSet(const string &val, uint64_t aligned_size = 0);
        explicit GWeiStrByteSet(const ByteSet &val) : StrByteSet(val) { }

        virtual operator string() const;

    private:
        virtual void construct(const string &val, uint64_t aligned_size);
};