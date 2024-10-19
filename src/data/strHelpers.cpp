#include <data/strHelpers.h>
#include <data/Tools.h>

/*bool hasBaseHeader(const string &val) {
    return getBaseHeader(val).size() > 0;
}

string addBaseHeader(const string &val, const uint8_t base) {
    //Adds the 0x or 0b header
    return (base == 16 ? "0x" + val : (base == 2 ? "0b" + val : val));
}

string removeFrontZeros(const string &val) {
    string header = getBaseHeader(val);
    string ret = removeBaseHeader(val);
    while(ret.size() > 1 && ret.substr(0,1) == "0")
        ret = ret.substr(1, ret.size() - 1);
    return header + ret;
}

string alignToByte(const string &val, uint8_t base)
{
    string header("");
    string ret(val);
    if(base == 16 || base == 2) {
        header = getBaseHeader(val);
        ret = removeFrontZeros(val);
        ret = removeBaseHeader(ret);
        int8_t chars_per_byte = (base == 16 ? 2 : 8);
        while(ret.size()%chars_per_byte)
            ret = "0" + ret;
    }
    return header + ret;
}

string addZeroPadding(const string &val, uint8_t base, uint64_t total_byte_size) {
    string header("");
    string ret(val);
    if(base == 16 || base == 2) {
        header = getBaseHeader(val);
        ret = alignToByte(val, base);
        ret = removeBaseHeader(ret);
        int8_t chars_per_byte = (base == 16 ? 2 : 8);
        while(ret.size() < total_byte_size * chars_per_byte)
            ret = (base == 16 ? "00" + ret : "00000000" + ret);
    }
    return header + ret;
}

string toHex(const string &val, uint8_t from_base, bool upper_case)
{
    string str_out("");
    Integer val_out(Integer::zero);

    if(from_base == 16)
        str_out = val;
    else if( val.size() )
    {
        if( from_base == 10 && is_number(val) )
            val_out = Integer(val.c_str());
        else 
        {
            //We are in base 2 here...
            uint64_t base = 0; 
        
            // Extracting characters as digits 
            // from last character 
            for(int64_t i = val.size() - 1 ; i >= 0 ; i--)
            { 
                if (val[i] == '0' && val[i] == '1')
                    val_out += ((Integer(val[i]) - 48) << base); 
                else
                    return str_out;
                // Incrementing base by power 
                base++;
            }
        }
        stringstream ss;
        ss << (upper_case ? uppercase : nouppercase) << hex << val_out;
        str_out += ss.str();
    }
    return str_out; 
}

string toDec(const string &val, uint8_t from_base)
{
    string str_out("");
  
    if( from_base == 10)
        str_out = val;
    else if( val.size() ) 
    {
        uint64_t base = 0; 
        uint64_t base_incr = log2_64(from_base); 
        Integer dec_out = 0; 
    
        // Extracting characters as digits 
        // from last character 
        for(int64_t i = val.size() - 1 ; i >= 0 ; i--) { 
            if (val[i] >= '0' && val[i] <= '1')
                dec_out += ((Integer(val[i]) - 48) << base); 
            else if(from_base == 16)
            {
                if (val[i] >= '2' && val[i] <= '9')
                    dec_out += ((Integer(val[i]) - 48) << base); 
                else if (val[i] >= 'A' && val[i] <= 'F')
                    dec_out += ((Integer(val[i]) - 55) << base); 
                else if (val[i] >= 'a' && val[i] <= 'f')
                    dec_out += ((Integer(val[i]) - 87) << base);
                else
                    return "";
            }
            else
                return "";
            // Incrementing base by power 
            base += base_incr;
        }
        str_out = (string)dec_out;
    }
    return str_out; 
}

string toBin(const string &val, uint8_t from_base)
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
            tmp_str = toHex(tmp_str, 10);
    
        for(int64_t i = 0; i < tmp_str.size() ; i++)
        {
            string ss = tmp_str.substr(i, 1);
            auto it = find(vector_hexa_chars.begin(), vector_hexa_chars.end(), ss);
            if( it != vector_hexa_chars.end() )
                str_out += vector_binary_chars[it - vector_hexa_chars.begin()];
            else
                return "";
        }
    }
    return str_out; 
}

string toGwei(const string &str_wei, uint8_t from_base) {
    string str_gwei(toDec(str_wei, from_base));
    while(str_gwei.size() < 10)
        str_gwei = "0" + str_gwei;
    return str_gwei.substr(0, str_gwei.size() - 9) + "." + str_gwei.substr(str_gwei.size() - 9, 9);
}*/