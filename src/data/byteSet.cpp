#include <data/byteSet.h>

template<class Derived, typename T>
Derived ValueVector<Derived, T>::pop_front(uint64_t nb_element) {
    Derived ret_value;
    assert(elemSize()>=nb_element);
    if(nb_element <= elemSize())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_back(pop_front());
    return ret_value;
}

template<class Derived, typename T>
Derived ValueVector<Derived, T>::pop_back(uint64_t nb_element) {
    Derived ret_value;
    assert(elemSize()>=nb_element);
    if(nb_element <= elemSize())
        for(uint64_t i=0;i<nb_element;i++)
            ret_value.push_front(pop_back());
    return ret_value;
}

template<class Derived, typename T>
T ValueVector<Derived, T>::pop_front()
{
    assert(elemSize());
    T ret_value = getElem(0);
    vvalue.erase(vvalue.begin());
    return ret_value;
}

template<class Derived, typename T>
T ValueVector<Derived, T>::pop_back()
{
    assert(elemSize());
    T ret_val = getElem(elemSize()-1);
    vvalue.pop_back();
    return ret_val;
}

template<typename T>
Integer byteSet<T>::right(uint64_t byte_size) const
{
    Integer ret_value = 0;
    for(uint64_t i=0;i<min(byte_size, ValueVector<T>::elemSize());i++)
        ret_value += (Integer(getElem(ValueVector<T>::elemSize()-1-i)) << (i*ValueVector<T>::getElemBitSize()));
    return ret_value;     
}

/*********************************************SPECIALIZATION*********************************************/

template<> uint8_t ValueVector<bool>::getElemBitSize() const { return 1; }
template<> uint8_t ValueVector<uint8_t>::getElemBitSize() const { return 8; }