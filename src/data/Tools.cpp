#include <data/Tools.h>

string base64_url_encode(const string & in)
{
    string out;
    int val =0, valb=-6;
    size_t len = in.length();
    unsigned int i = 0;
    for (i = 0; i < len; i++)
    {
        unsigned char c = in[i];
        val = (val<<8) + c;
        valb += 8;
        while (valb >= 0)
        {
            out.push_back(base64_url_alphabet[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6)
        out.push_back(base64_url_alphabet[((val<<8)>>(valb+8))&0x3F]);
    return out;
}

string base64_url_decode(const string & in)
{
    string out;
    vector<int> T(256, -1);
    unsigned int i;
    for (i =0; i < 64; i++)
        T[base64_url_alphabet[i]] = i;

    int val = 0, valb = -8;
    for (i = 0; i < in.length(); i++)
    {
        unsigned char c = in[i];
        if (T[c] == -1)
            break;
        val = (val<<6) + T[c];
        valb += 6;
        if (valb >= 0)
        {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}

vector<string> split(const string& list, const string& separator)
{
    vector<string> v;   
    int start = 0;
    int end = list.find(separator);
    while (end != -1) {
        if(end > start ) v.push_back(list.substr(start, end - start));
        start = end + separator.size();
        end = list.find(separator, start);
    }
    if(start != list.size()) v.push_back(list.substr(start, list.size() - start));
    return v;
}

bool isPrimeNumber(const Integer& n)
{
   bool isPrime = true;

   for(Integer i = 2; i*i <= n; i++) {
      if (n%i == 0) {
         isPrime = false;
         break;
      }
   }  
   return isPrime;
}

string changeBase(const string& str_in, uint8_t to_base, uint64_t to_size, uint8_t from_base)
{
    string str_out(to_base == 16 ? "0x" : "0b");
    Integer dec_out(Integer::zero);

    if( str_in.size() )
    {
        string tmp_in(str_in);

        if( tmp_in.size() >=2 ) {
            if( tmp_in.substr(0,2) == "0x" ) {
                //Removes the 0x header if necessary
                tmp_in = tmp_in.substr(2, tmp_in.size() - 2);
                from_base = 16;
            }
            else if( tmp_in.substr(0,2) == "0b" ) {
                //Removes the 0b header if necessary
                tmp_in = tmp_in.substr(2, tmp_in.size() - 2);
                from_base = 2;
            }
        }

        if( from_base == 10 ) {
            //Converts a decimal string into an hexa string via Integer
            stringstream ss;
            ss << std::hex << Integer(str_in.c_str());
            tmp_in = ss.str();
            from_base = 16;
        }

        // Removes input front "0" to reach the value
        while(tmp_in.substr(0,1) == "0")
            tmp_in = tmp_in.substr(1, tmp_in.size() - 1);
        // ...and full byte padding
        if( from_base == 2 )
            while(tmp_in.size()%8) tmp_in = "0" + tmp_in;
        else if( from_base == 16 )
            while(tmp_in.size()%2) tmp_in = "0" + tmp_in;
        // Adds front "0" to reach to_size if specified
        while( tmp_in.size() < (to_size << (from_base == 16 ? 1: 3)))
            tmp_in =  (from_base == 16 ? "00" : "00000000") + tmp_in;

        auto from_vec(from_base == 16 ? vector_hexa_chars : vector_binary_chars);
        auto to_vec(to_base == 16 ? vector_hexa_chars : vector_binary_chars);
        uint8_t nibble_size = (from_base == 16 ? 1 : 4);
        while(tmp_in.size()>0)
        {
            string ss = tmp_in.substr(0, nibble_size);
            auto it = find(from_vec.begin(), from_vec.end(), ss);
            assert( it != from_vec.end() );
            int index = it - from_vec.begin();
            if( to_base == 10 ) {
                dec_out <<= 4;
                //%16 allows to search for hex values in both upper&lower case
                dec_out += index%16;
            }
            else
                //%16 allows to search for hex values in both upper&lower case
                str_out += to_vec[index%16];
            tmp_in = tmp_in.substr(nibble_size, tmp_in.size() - nibble_size);
        }
    }
    return (to_base == 10 ? dec_out : str_out);
}

string toGwei(const string& str_wei) {
    string str_gwei(str_wei);
    while(str_gwei.size() < 10)
        str_gwei = "0" + str_gwei;
    return str_gwei.substr(0, str_gwei.size() - 9) + "." + str_gwei.substr(str_gwei.size() - 9, 9);
}