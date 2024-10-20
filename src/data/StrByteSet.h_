#pragma once

#include <data/ByteSet.h>
#include <data/strHelpers.h>

class StrByteSet : public ByteSet
{
    public:
        enum class Format{INVALID = 0, BIN, BIN_H = 2, DEC = 10, GWEI, HEX, HEX_H = 16};

        /// @brief Copy constructor
        /// @param str 
        StrByteSet(const StrByteSet &str);

        /// @brief Constructor from a STRICT valid string value
        /// @param val valid value string WITH base header
        /// @param aligned_size either a total byte-size required for 0-padding
        /// or 0 let the constructor apply a simple byte-padding and guess the underlying value size.
        StrByteSet(const string &val, uint64_t aligned_size = 0, uint8_t base = 0);

        inline void setFormat(Format f) { m_default_format = f; }

        /// @brief string operator returning the default representation
        /// @return Size in Bytes of the value represented by the hex/bin strings, 0-padding included.
        /// The dec/Gwei strings being not aligned, their size is not relevant here
        operator string() const;

    private:
        string toHex(const string &val, uint8_t from_base) const;
        string toDec(const string &val, uint8_t from_base) const;
        string toBin(const string &val, uint8_t from_base) const;
        string toGwei(const string &val, uint8_t from_base) const;

        string getBaseHeader(const string &val) const;
        uint8_t getBase(const string &val) const;
        string removeBaseHeader(const string &val);

        string alignToByte(const string &val, uint64_t aligned_size, uint8_t base) const;
        string removeFrontZeros(const string &val) const;

        uint8_t charToNibble(const char &c) const;
        char nibbleToChar(const uint8_t &nibble) const;
        
        void removeChars(string &str, const char* charsToRemove );

    private:
        string m_hex;
        string m_dec;
        string m_gwei;
        string m_bin;
        /// @brief Defines the prefered format when cast to string
        Format m_default_format;
};