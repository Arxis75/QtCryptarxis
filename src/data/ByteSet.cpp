#include <data/ByteSet.h>
#include <crypto/System.h> 

ByteSet ByteSet::pop_front(uint64_t nb_element) {
    ByteSet ret_value;
    //assert(byteSize()>=nb_element);
    if(nb_element <= byteSize())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_back(pop_front());
    return ret_value;
}

ByteSet ByteSet::pop_back(uint64_t nb_element) {
    ByteSet ret_value;
    //assert(byteSize()>=nb_element);
    if(nb_element <= byteSize())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_front(pop_back());
    return ret_value;
}

uint8_t ByteSet::pop_front()
{
    assert(byteSize());
    uint8_t ret_value = vvalue[0];
    vvalue.erase(vvalue.begin());
    return ret_value;
}

uint8_t ByteSet::pop_back()
{
    assert(byteSize());
    uint8_t ret_val = vvalue[byteSize()-1];
    vvalue.pop_back();
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