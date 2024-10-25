#include <data/byteSet.h>

template<class Derived, typename T>
Derived ValueVector<Derived, T>::pop_front(uint64_t nb_element) {
    Derived ret_value;
    assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_back(pop_front());
    return ret_value;
}

template<class Derived, typename T>
Derived ValueVector<Derived, T>::pop_back(uint64_t nb_element) {
    Derived ret_value;
    assert(nbElements()>=nb_element);
    if(nb_element <= nbElements())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_front(pop_back());
    return ret_value;
}

template<class Derived, typename T>
T ValueVector<Derived, T>::pop_front()
{
    assert(nbElements());
    T ret_value = getElem(0);
    vvalue.erase(vvalue.begin());
    return ret_value;
}

template<class Derived, typename T>
T ValueVector<Derived, T>::pop_back()
{
    assert(nbElements());
    T ret_val = getElem(nbElements()-1);
    vvalue.pop_back();
    return ret_val;
}

template<typename T>
Integer byteSet<T>::toInteger(uint64_t nb_right_bits) const
{
    Integer ret_value = 0;
    uint64_t i_end = min(ValueVector<T>::nbElements(), nb_right_bits/ValueVector<T>::elemValueBitSize());
    for(uint64_t i=0;i<i_end;i++)
        ret_value += (Integer(getElem(ValueVector<T>::nbElements()-1-i)) << (i*ValueVector<T>::getElemBitSize()));
    return ret_value;     
}
/*********************************************SPECIALIZATION*********************************************/

template<> uint8_t ValueVector<bool>::elemValueBitSize() const { return 1; }
template<> uint8_t ValueVector<uint8_t>::elemValueBitSize() const { return 8; }