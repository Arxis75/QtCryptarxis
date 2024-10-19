#include "HexStrByteSet.h"

#include <data/Tools.h>

HexStrByteSet::HexStrByteSet(const string &val, uint64_t aligned_size)
    : IntByteSet(Integer::zero, aligned_size)
{
    regex rgx_hex("^(0x)?[0-9a-fA-F]+");

    if( regex_match(val, rgx_hex) )
    {
        //Constructing the ByteSet representations
        string str = alignToByte(removeBaseHeader(val), aligned_size);

        //Constructing the parent ByteSet itself
        uint8_t i_byte;
        while(str.size()) {
            // Treating each nibble pair
            i_byte = (charToNibble(str[0]) << 4);
            i_byte += charToNibble(str[1]);
            vvalue.push_back(i_byte);
            str = str.substr(2, str.size() - 2);
        }
    }
}

HexStrByteSet::operator string() const
{
    string str;
    for(uint64_t i=0;i<byteSize();i++) {
        str += nibbleToChar((vvalue[i] & 0xF0) >> 4);
        str += nibbleToChar( vvalue[i] & 0x0F);
    }
    return "0x" + str;
}

//TODO: move to parent abstract class
string HexStrByteSet::removeBaseHeader(const string &val) {
    string str_out = val;
    //Removes the 0x or 0b header if necessary
    if(val.size() >= 2 && val.substr(0, 2) ==  "0x")
        str_out = val.substr(2, val.size() - 2);
    return str_out;
}

string HexStrByteSet::alignToByte(const string &val, uint64_t aligned_size) const
{
    string str_out = val;
    int8_t chars_per_byte = 2;
    uint8_t unaligned_size = str_out.size()%chars_per_byte;
    string str_unaligned = str_out.substr(0, unaligned_size);
    if( unaligned_size ) {
        if( str_out.size() > unaligned_size &&   // don't remove the 0s if there is nothing else!
            str_unaligned == string(unaligned_size, '0') )
            //removes extra 0s
            str_out = str_out.substr(unaligned_size, str_out.size() - unaligned_size);
        else
            while(str_out.size()%chars_per_byte)
                //adds extra 0s
                str_out = "0" + str_out;
    }
    while(str_out.size() < aligned_size * chars_per_byte)
        //adds padding 0s if necessary
        str_out = string(chars_per_byte, '0') + str_out;
    return str_out;
}

uint8_t HexStrByteSet::charToNibble(const char &c) const
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

char HexStrByteSet::nibbleToChar(const uint8_t &nibble) const
{
    char c;
    if (nibble >= 0 && nibble <= 9)
        c = 48 + nibble;
    else if (nibble >= 0xA && nibble <= 0xF)
        c = 87 + nibble;
    return c;
}