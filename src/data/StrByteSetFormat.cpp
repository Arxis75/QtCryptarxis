#include <data/StrByteSetFormat.h>

StrByteSetFormat::StrByteSetFormat(
        const string &UIName,
        const string &Header,
        uint8_t Base,
        uint8_t BitsPerChar,
        const string &Regex,
        uint8_t aligned_byte_size,
        uint8_t Exp)
    : m_ui_name(UIName)
    , m_header(Header)
    , m_base(Base)
    , m_bits_per_char(BitsPerChar)
    , m_regex(Regex)
    , m_aligned_byte_size(aligned_byte_size)
    , m_exp(Exp)
{ }

string StrByteSetFormat::toCanonicalString(const string& val) const
{
    string ret_val;
    if( regex_match(val, regex(m_regex)) )
        ret_val = removeExp(removeHeader(val));
    return ret_val;
}

string StrByteSetFormat::toUserString(const string& val) const
{
    return addHeader(val.size() ? addExp(val) : val);
}

string StrByteSetFormat::addHeader(const string& val) const
{
    return m_header + val;
}

string StrByteSetFormat::removeHeader(const string& val) const
{
    string ret_val = val;
    //Removes the Header
    if(val.size() >= m_header.size() && val.substr(0, m_header.size()) == m_header)
        ret_val = val.substr(m_header.size(), val.size() - m_header.size());
    return ret_val;
}

string StrByteSetFormat::addExp(const string& val) const
{
    string str_exp = val;
    if(m_exp) {
        while(str_exp.size() <= m_exp)
            str_exp = "0" + str_exp;
        str_exp = str_exp.substr(0, str_exp.size() - m_exp) + "." + str_exp.substr(str_exp.size() - m_exp, m_exp);
    }
    return str_exp;
}

string StrByteSetFormat::removeExp(const string& val) const
{
    string ret_val = val;
    if(m_exp) {
        vector<string> v = split(ret_val, ".");
        if(v.size() == 1)
            //Create fractionnal part if missing
            v.push_back("");
        if(v.size() == 2 && v[1].size() < m_exp)
            for(int i=v[1].size();i<m_exp;i++)
                //Add right-side 0-padding if needed
                ret_val += "0";
        //Removes the Exponentiation separator
        ret_val = removeCharsFromString(ret_val.c_str(), ".");
    }
    return ret_val;
}

string StrByteSetFormat::removeCharsFromString(const string &val, const char* charsToRemove) const
{
    string str_out = val;
    for (uint8_t i = 0; i < strlen(charsToRemove); ++i ) {
        str_out.erase( remove(str_out.begin(), str_out.end(), charsToRemove[i]), str_out.end() );
    }
    return str_out;
}