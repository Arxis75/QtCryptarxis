#pragma once

#include <data/StrByteSetFormat.h>
#include <data/ByteSet.h>
#include <crypto/bip39_dictionnary.h>

class BIP39MnemonicFormat : public StrByteSetFormat
{
    public:
        BIP39MnemonicFormat( const string &UIName,
                             const string &Regex,
                             uint16_t entropy = 256,
                             const vector<string> *dictionnary = &BIP39::Dictionary::WordList_english);

        inline bool operator==(const BIP39MnemonicFormat& b) const { return (const StrByteSetFormat)(*this) == (const StrByteSetFormat)(b) && m_dic == b.m_dic && m_ms == b.m_ms; }
        inline bool operator!=(const BIP39MnemonicFormat& b) const { return !(*this == b); }
        
        virtual string toUserString(const string& val) const override;

        inline uint8_t getWordEntropyBitSize() const { return m_went; }
        inline uint8_t getEntropyBitSize() const { return m_ent; }
        inline uint8_t getNbWords() const { return m_ms; }
        inline uint8_t getChecksumBitSize() const { return m_ms; }
        inline vector<string> const* getDictionnary() const { return m_dic; }

    protected:
        virtual string _toCanonicalString(const string& val) const override;

        inline ByteSet<bool> checksum(const ByteSet<bool>& val) const { return val.sha256().left(m_cs); }
        inline bool isValid(const ByteSet<bool> &cs_ent) const { return cs_ent.bitSize() == m_ms * m_went && cs_ent.right(m_cs) == checksum(cs_ent.left(m_ent)); }
        
        string toLowerCase(const string &word) const;
        inline vector<string>::const_iterator toDicIter(const string& word) const { return find(m_dic->begin(), m_dic->end(), word); }
        inline uint64_t toDicIndex(vector<string>::const_iterator iter) const { return std::distance(m_dic->begin(), iter); }

    private:
        const vector<string> *m_dic;
        uint8_t m_went;
        uint16_t m_ent;
        uint8_t m_ms;
        uint8_t m_cs;
};

/// @brief BIP39 mnemonics
static const BIP39MnemonicFormat Bip39Mnemonic12("12-words", "^\\s*([a-zA-Z]+\\s*){0,12}$", 128, &BIP39::Dictionary::WordList_english);
static const BIP39MnemonicFormat Bip39Mnemonic15("15-words", "^\\s*([a-zA-Z]+\\s*){0,15}$", 160, &BIP39::Dictionary::WordList_english);
static const BIP39MnemonicFormat Bip39Mnemonic18("18-words", "^\\s*([a-zA-Z]+\\s*){0,18}$", 192, &BIP39::Dictionary::WordList_english);
static const BIP39MnemonicFormat Bip39Mnemonic21("21-words", "^\\s*([a-zA-Z]+\\s*){0,21}$", 224, &BIP39::Dictionary::WordList_english);
static const BIP39MnemonicFormat Bip39Mnemonic24("24-words", "^\\s*([a-zA-Z]+\\s*){0,24}$", 256, &BIP39::Dictionary::WordList_english);
