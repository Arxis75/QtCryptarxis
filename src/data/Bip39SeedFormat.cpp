#include <data/Bip39SeedFormat.h>

BIP39MnemonicFormat::BIP39MnemonicFormat(const string &UIName,const string &Regex, uint16_t entropy, const vector<string> *dictionnary)
    : StrByteSetFormat(UIName, "", 2, 1, Regex, 0, 0)
    , m_ent(entropy)
    , m_dic(dictionnary ? dictionnary : &BIP39::Dictionary::WordList_english)
{ 
    assert(m_ent == 128 || m_ent == 160 || m_ent == 192 || m_ent == 224 || m_ent == 256);

    m_went = log2(m_dic->size());

    div_t d = div(m_ent, m_went);
    m_ms = d.quot + 1;              // 1 extra word for checksum/alignment
    m_cs = m_went - d.rem;
}

string BIP39MnemonicFormat::_toCanonicalString(const string& words_list) const
{
    ByteSet<bool> cs_ent;
    vector<string> v = split(words_list, " ");
    if (v.size() <= m_ms)
        for (int i = 0; i < v.size(); i++)
            if(auto iter = toDicIter(toLowerCase(v[i])); iter != m_dic->end())
                cs_ent.push_back(ByteSet<bool>(toDicIndex(iter), m_went));
    return (v.size() < m_ms || isValid(cs_ent)) ? Bin.toCanonicalString(StrByteSet<Bin, bool>(cs_ent.left(m_ent))) : "";
}

string BIP39MnemonicFormat::toUserString(const string& entropy) const
{
    string word_list;
    StrByteSet<Bin, bool> val(entropy);
    if(val.bitSize() <= m_ent) {
        for(int i=0;i<(val.bitSize()/m_went);i++)
            word_list += m_dic->at(val.get(i*m_went,m_went)) + (i == m_ms - 1 ? "" : " ");
        if(val.bitSize() == m_ent)
            word_list += m_dic->at((val.right(m_went-m_cs) << m_cs) + (uint64_t)checksum(val));
    }
    return word_list;
}

string BIP39MnemonicFormat::toLowerCase(const string &word) const
{
    string lc_word = word;
    std::transform(lc_word.begin(), lc_word.end(), lc_word.begin(), ::tolower);
    return lc_word;
}
