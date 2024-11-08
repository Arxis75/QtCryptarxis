#pragma once

#include <data/Tools.h>

class StrByteSetFormat
{
    public:
        StrByteSetFormat(const string &UIName,
                         const string &Header,
                         uint8_t Base,
                         uint8_t BitsPerChar,
                         const string &Regex,
                         uint8_t Exp);

        inline bool operator==(const StrByteSetFormat& b) const { return m_ui_name == b.m_ui_name && m_header == b.m_header && m_base == b.m_base && m_bits_per_char == b.m_bits_per_char && m_regex == b.m_regex && m_exp == b.m_exp; }
        inline bool operator!=(const StrByteSetFormat& b) const { return !(*this == b); }
        inline operator string() const { return getUIName(); }

        inline const string &getUIName() const { return m_ui_name; }
        inline const string &getHeader() const { return m_header; }
        inline uint8_t getBase() const { return m_base; }
        inline uint8_t getBitsPerChar() const { return m_bits_per_char; }
        inline const string &getRegex() const { return m_regex; }
        inline uint8_t getExp() const { return m_exp; }
        inline bool isAligned() const { return getBase() == 16 || getBase() == 2; }

        string toCanonicalString(const string& val) const;
        string toUserString(const string& val) const;

    protected:
        string addHeader(const string& val) const;
        string removeHeader(const string& val) const;
        string addExp(const string& val) const;
        string removeExp(const string& val) const;

        string removeCharsFromString(const string &val, const char* charsToRemove) const;

    private:
        string m_ui_name;
        string m_header;
        uint8_t m_base;
        uint8_t m_bits_per_char;
        string m_regex;
        bool m_upper_case;
        uint8_t m_exp;
};

/// @brief Main Bases: 16 / 10 / 2
static const StrByteSetFormat Hex(  "Hex", "0x", 16, 4, "^(0x)?[0-9a-fA-F]+",           0);
static const StrByteSetFormat Dec(  "Dec",   "", 10, 0, "^[0-9]+",                      0);
static const StrByteSetFormat Bin(  "Bin", "0b",  2, 1, "^(0b)?[0-1]+",                 0);

/// @brief Alternative Decimals
static const StrByteSetFormat Wei(  "wei",   "", 10, 0, "^[0-9]+",                      0);
static const StrByteSetFormat Gwei( "Gwei",  "", 10, 0, "^[0-9]+.[0-9]{0,9}",           9);
static const StrByteSetFormat Eth(  "Eth",   "", 10, 0, "^[0-9]+.[0-9]{0,18}",         18);

/// @brief Alternative Hexadecimals
static const StrByteSetFormat Hex20("Hex", "0x", 16, 4, "^(0x)?[0-9a-fA-F]{0,40}",      0); // Addresses
static const StrByteSetFormat Hex32("Hex", "0x", 16, 4, "^(0x)?[0-9a-fA-F]{0,64}",      0); // Private Keys, Signature R, Signature S...
static const StrByteSetFormat Hex33("Hex", "0x", 16, 4, "^(0x)?0[2|3][0-9a-fA-F]{64}",  0); // Compressed PubKeys
static const StrByteSetFormat Hex64("Hex", "0x", 16, 4, "^(0x)?[0-9a-fA-F]{0,128}",     0); // BIP39 Seeds

