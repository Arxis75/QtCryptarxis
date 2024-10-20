#include "ArrayByteSet.h"

#include <crypto/System.h>

ArrayByteSet::ArrayByteSet(const uint8_t *p, uint64_t aligned_size)
    : RawStrByteSet()
{
    for(uint64_t i=0;i<aligned_size;i++)
        vvalue.push_back(p[i]);
}