#include "StrByteSet.h"

#include <data/Tools.h>

StrByteSet::StrByteSet(const StrByteSet &str)
    : ByteSet(str)
    , m_hex(str.m_hex)
    , m_dec(str.m_dec)
    , m_gwei(str.m_gwei)
    , m_bin(str.m_bin)
{ }

StrByteSet::StrByteSet(const string &val, uint64_t aligned_size, uint8_t base)
    : ByteSet()
    , m_default_format((Format)base)
{
    if(!base)
        base = getBase(val);
    assert( base == 16 || base == 10 || base == 2);

    regex rgx_hex("^(0x)?[0-9a-fA-F]+");
    regex rgx_dec("^[0-9]+");
    regex rgx_gwei("^[0-9]+\\.[0-9]{9}$");
    regex rgx_bin("^(0b)?[0-1]+");

    if ( base == (uint8_t)Format::HEX_H && regex_match(val, rgx_hex) || 
         base == (uint8_t)Format::HEX && regex_match(val, rgx_hex) || 
         base == (uint8_t)Format::DEC && regex_match(val, rgx_dec) ||
         base == (uint8_t)Format::GWEI && regex_match(val, rgx_gwei) ||
         base == (uint8_t)Format::BIN_H && regex_match(val, rgx_bin) ||
         base == (uint8_t)Format::BIN && regex_match(val, rgx_bin) )
    {
        string str = removeBaseHeader(val);

        if( base == (uint8_t)Format::GWEI ) {
            removeChars(str, ".");
            base = 10;
        }

        //Constructing the ByteSet representations
        m_hex = alignToByte(toHex(str, base), 16, aligned_size);
        m_dec = removeFrontZeros(toDec(str, base));
        m_gwei = toGwei(m_dec, 10);
        m_bin = alignToByte(toBin(str, base), 2, aligned_size); 

        //Constructing the parent ByteSet itself
        string tmp_str(m_hex);
        uint8_t i_byte;
        if(tmp_str.size()%2) {
            // Treating a possible odd front nibble
            i_byte = charToNibble(tmp_str[0]);
            vvalue.push_back(i_byte);
            tmp_str = tmp_str.substr(1, tmp_str.size() - 1);
        }
        while(tmp_str.size()) {
            // Treating each nibble pair
            i_byte = (charToNibble(tmp_str[0]) << 4);
            i_byte += charToNibble(tmp_str[1]);
            vvalue.push_back(i_byte);
            tmp_str = tmp_str.substr(2, tmp_str.size() - 2);
        }
    }
}

string StrByteSet::toHex(const string &val, uint8_t from_base) const
{
    string str_out("");

    if(from_base == 16)
        str_out = val;
    else if( val.size() )
    {
        if( from_base == 10) {
            Integer val_out(val.c_str());
            stringstream ss;
            ss << hex << val_out;
            str_out = ss.str();
        }
        else 
        {   // base = 2
            string tmp_str(val);
            uint8_t i_nibble = 0;
            if(tmp_str.size()%4) {
                while(tmp_str.size()%4) {
                    // Treating possible single front bits
                    i_nibble += charToNibble(tmp_str[0]);
                    tmp_str = tmp_str.substr(1, tmp_str.size() - 1);
                }
                str_out += nibbleToChar(i_nibble);
            }
            while(tmp_str.size()) {
                // Treating each nibble
                i_nibble = (charToNibble(tmp_str[0]) << 3);
                i_nibble += (charToNibble(tmp_str[1]) << 2);
                i_nibble += (charToNibble(tmp_str[2]) << 1);
                i_nibble += (charToNibble(tmp_str[3]));
                str_out += nibbleToChar(i_nibble);
                tmp_str = tmp_str.substr(4, tmp_str.size() - 4);
            }
        }
    }
    return str_out; 
}


string StrByteSet::toDec(const string &val, uint8_t from_base) const
{
    string str_out("");
  
    if( from_base == 10)
        str_out = val;
    else if( val.size() ) 
    {
        Integer dec_out = 0; 
        uint64_t nibble_incr = log2_64(from_base); 
        
        // Extracting characters as digits 
        // from last character 
        for(int64_t i = 0 ; i < val.size() ; i++) {
            dec_out <<= nibble_incr; 
            dec_out += charToNibble(val[i]); 
        }
        str_out = (string)dec_out;
    }
    return str_out; 
}

string StrByteSet::toGwei(const string &str_wei, uint8_t from_base) const {
    string str_gwei(toDec(str_wei, from_base));
    while(str_gwei.size() < 10)
        str_gwei = "0" + str_gwei;
    return str_gwei.substr(0, str_gwei.size() - 9) + "." + str_gwei.substr(str_gwei.size() - 9, 9);
}

string StrByteSet::toBin(const string &val, uint8_t from_base) const
{
    const vector<const char*> vector_hexa_chars = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                                                    "a", "b", "c", "d", "e", "f",
                                                    "A", "B", "C", "D", "E", "F" };
    const vector<const char*> vector_binary_chars = { "0000", "0001", "0010", "0011", "0100", "0101",
                                                      "0110", "0111", "1000", "1001",
                                                      "1010", "1011", "1100", "1101", "1110", "1111",
                                                      "1010", "1011", "1100", "1101", "1110", "1111" };
    string str_out("");
  
    if( from_base == 2)
        str_out = val;
    else if( val.size() )
    {
        string tmp_str(val);
       
        if(from_base == 10)
            tmp_str = toHex(val, 10);
    
        // Base = 16
        for(int64_t i = 0; i < tmp_str.size() ; i++)
        {
            string ss = tmp_str.substr(i, 1);
            auto it = find(vector_hexa_chars.begin(), vector_hexa_chars.end(), ss);
            if( it != vector_hexa_chars.end() )
                str_out += vector_binary_chars[it - vector_hexa_chars.begin()];
        }
    }
    return str_out; 
}

StrByteSet::operator string() const
{
    string str_out;
    switch(m_default_format) {
        case Format::BIN:
            str_out = m_bin;
        break;
        case Format::BIN_H:
            str_out = "0b" + m_bin;
        break;
        case Format::DEC:
            str_out = m_dec;
        break;
        case Format::GWEI:
            str_out = m_gwei;
        break;
        case Format::HEX:
            str_out = m_hex;
        break;
        case Format::HEX_H:
        default:
            str_out = "0x" + m_hex;
        break;
    }
    return str_out;
}

string StrByteSet::getBaseHeader(const string &val) const {
    //Checks the presence of the 0x or 0b header
    string header("");
    if(val.size() >= 2) {
        header = val.substr(0,2);
        if(header != "0x" & header != "0b" )
            header.clear();
    }
    return header;
}

uint8_t StrByteSet::getBase(const string &val) const {
    string header = getBaseHeader(val);
    return header == "0x" ? 16 : ( header == "0b" ? 2 : 10);
}

string StrByteSet::removeBaseHeader(const string &val) {
    string str_out = val;
    //Removes the 0x or 0b header if necessary
    if(int header_size = getBaseHeader(str_out).size())
        str_out = str_out.substr(header_size, str_out.size() - header_size);
    return str_out;
}

string StrByteSet::alignToByte(const string &val, uint64_t aligned_size, uint8_t base) const
{
    string str_out = val;
    if(base == 16 || base == 2) {
        int8_t chars_per_byte = (base == 16 ? 2 : 8);
        uint8_t unaligned_size = str_out.size()%chars_per_byte;
        string str_unaligned = str_out.substr(0, unaligned_size);
        if( unaligned_size ) {
            if( str_out.size() > unaligned_size &&   // don't remove the 0s if there is nothing else!
                (str_unaligned == "0" || str_unaligned == "00"
                || str_unaligned == "000" || str_unaligned == "0000"
                || str_unaligned == "00000" || str_unaligned == "000000"
                || str_unaligned == "0000000") )
                //removes extra 0s
                str_out = str_out.substr(unaligned_size, str_out.size() - unaligned_size);
            else
                while(str_out.size()%chars_per_byte)
                    //adds extra 0s
                    str_out = "0" + str_out;
        }
        while(str_out.size() < aligned_size * chars_per_byte)
            //adds padding 0s if necessary
            str_out = (base == 16 ? "00" : "00000000") + str_out;
    }
    return str_out;
}

string StrByteSet::removeFrontZeros(const string &val) const {
    string ret = val;
    while(ret.size() > 1 && ret.substr(0,1) == "0")
        ret = ret.substr(1, ret.size() - 1);
    return ret;
}

uint8_t StrByteSet::charToNibble(const char &c) const
{
    uint8_t retval = 0;
    if (c >= '0' && c <= '9')
        retval = c - 48;
    else if (c >= 'A' && c <= 'F')
        retval = c - 55;
    else if (c >= 'a' && c <= 'f')
        retval = c - 87;
    return retval;
}

char StrByteSet::nibbleToChar(const uint8_t &nibble) const
{
    char c;
    if (nibble >= 0 && nibble <= 9)
        c = 48 + nibble;
    else if (nibble >= 0xA && nibble <= 0xF)
        c = 87 + nibble;
    return c;
}

void StrByteSet::removeChars(string &str, const char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}