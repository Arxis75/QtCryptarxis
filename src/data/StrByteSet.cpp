#include "StrByteSet.h"

#include <data/Tools.h>

StrByteSet::StrByteSet(const string &val, const string &header, const string &regex, bool is_aligned, uint8_t chars_per_byte, uint64_t aligned_size)
    : IntByteSet()
    , m_header(header)
    , m_regex(regex)
    , m_is_aligned(is_aligned)
    , m_chars_per_byte(chars_per_byte)
{
    if( regex_match(val, m_regex) )
        construct(val, aligned_size);
}

void StrByteSet::construct(const string &val, uint64_t aligned_size)
{
    //Constructing the ByteSet representations
    string str = alignToByte(removeBaseHeader(val), aligned_size);

    if(m_is_aligned) {
        //Constructing the parent ByteSet itself
        uint8_t i_byte;
        while(str.size()) {
            i_byte = 0;
            // Treating each byte
            for(uint8_t i=0;i<m_chars_per_byte;i++)
                i_byte += (charToNibble(str[m_chars_per_byte - 1 - i]) << (i*8/m_chars_per_byte));
            vvalue.push_back(i_byte);
            str = str.substr(m_chars_per_byte, str.size() - m_chars_per_byte);
        }
    }
}

StrByteSet::operator string() const
{
    string str;
    if(m_is_aligned) {
        uint8_t mask = (0xFF >> m_chars_per_byte);
        for(uint64_t i=0;i<byteSize();i++)
            for(uint8_t j=0;i<m_chars_per_byte;j++)
                str += (nibbleToChar(vvalue[i] & mask) >> (j*8/m_chars_per_byte));            
        str = m_header + str;
    }
    return str;
}

            str += nibbleToChar( vvalue[i] & 0x0F);
            str += nibbleToChar((vvalue[i] & 0xF0) >> 4);

BinStrByteSet::operator string() const
{
    string str;
    for(uint64_t i=0;i<byteSize();i++) {
        str += nibbleToChar((vvalue[i] & 0b10000000) >> 7);
        str += nibbleToChar((vvalue[i] & 0b01000000) >> 6);
        str += nibbleToChar((vvalue[i] & 0b00100000) >> 5);
        str += nibbleToChar((vvalue[i] & 0b00010000) >> 4);
        str += nibbleToChar((vvalue[i] & 0b00001000) >> 3);
        str += nibbleToChar((vvalue[i] & 0b00000100) >> 2);
        str += nibbleToChar((vvalue[i] & 0b00000010) >> 1);
        str += nibbleToChar( vvalue[i] & 0b00000001);
    }
    return str;
}

string StrByteSet::removeBaseHeader(const string &val) {
    string str_out = val;
    //Removes the header if present
    if(val.size() >= m_header.size() && val.substr(0, m_header.size()) ==  m_header)
        str_out = val.substr(m_header.size(), val.size() - m_header.size());
    return str_out;
}

string StrByteSet::alignToByte(const string &val, uint64_t aligned_size) const
{
    string str_out = val;
    uint8_t unaligned_size = str_out.size()%m_chars_per_byte;
    string str_unaligned = str_out.substr(0, unaligned_size);
    if( unaligned_size ) {
        if( str_out.size() > unaligned_size &&   // don't remove the 0s if there is nothing else!
            str_unaligned == string(unaligned_size, '0') )
            //removes extra 0s
            str_out = str_out.substr(unaligned_size, str_out.size() - unaligned_size);
        else
            while(str_out.size()%m_chars_per_byte)
                //adds extra 0s
                str_out = "0" + str_out;
    }
    while(str_out.size() < aligned_size * m_chars_per_byte)
        //adds padding 0s if necessary
        str_out = string(m_chars_per_byte, '0') + str_out;
    return str_out;
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