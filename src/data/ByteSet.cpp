#include <data/ByteSet.h>
#include <data/StrByteSet.h>
#include <crypto/System.h>  //To improve: ByteSet should provide operator as input for external Hashing functions

ByteSet ByteSet::pop_front(uint64_t nb_element) {
    vector<uint8_t> ret_v;
    if(byteSize() && nb_element) {
        ret_v = vector<uint8_t>(vvalue.begin(), vvalue.begin() + min(byteSize(), nb_element));
        vvalue = vector<uint8_t>(vvalue.begin() + min(byteSize(), nb_element), vvalue.end());
    }
    return (ByteSet)ret_v;
}

ByteSet ByteSet::pop_back(uint64_t nb_element) {
    vector<uint8_t> ret_v;
    if(byteSize() && nb_element) {
        ret_v = vector<uint8_t>(vvalue.begin() + min(byteSize(), nb_element), vvalue.end());
        vvalue = vector<uint8_t>(vvalue.begin(), vvalue.begin() + min(byteSize(), nb_element));
    }
    return (ByteSet)ret_v;
}

uint8_t ByteSet::pop_front()
{
    uint8_t ret_val = 0;
    if(byteSize())
        ret_val = vector<uint8_t>(pop_front(1))[0];
    return ret_val;
}

uint8_t ByteSet::pop_back()
{
    uint8_t ret_val = 0;
    if(byteSize()) {
        ret_val = vvalue[byteSize()-1];
        vvalue.pop_back();
    }
    return ret_val;
}

uint8_t ByteSet::operator[](uint64_t index) const
{
    uint8_t ret_val = 0;
    if(index < byteSize())
        ret_val = vvalue[index];
    return ret_val;
}

ByteSet ByteSet::sha256() const
{
    ByteSet digest(32);
    if(byteSize())
        SHA256(&vvalue[0], byteSize(), &digest.vvalue[0]);
    return digest;
}

ByteSet ByteSet::keccak256() const
{
    ByteSet digest;
    if(byteSize()) {
        hash256 h = ethash::keccak256(&vvalue[0], byteSize());
        for(uint64_t i=0;i<32;i++)
            digest.push_back(h.bytes[i]);
    }
    return digest;
}

ByteSet ByteSet::generateRandom(uint32_t size)
{
    int retval = -1;
    ByteSet random_buffer(size), random_set(size);
    retval = RAND_bytes(&random_buffer.vvalue[0], size);

    if( retval > 0 )
        for(uint64_t i=0;i<size;i++)
            random_set.push_back(random_buffer.vvalue[i]);
    return random_set;
}