#include <data/byteSet.h>

/************************************************ ValueVector ************************************************/

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
    T ret_value = vvalue[0];
    vvalue.erase(vvalue.begin());
    return ret_value;
}

template<class Derived, typename T>
T ValueVector<Derived, T>::pop_back()
{
    assert(nbElements());
    T ret_val = vvalue[nbElements()-1];
    vvalue.pop_back();
    return ret_val;
}

/************************************************ byteSet ************************************************/

template<typename T>
Integer byteSet<T>::toInteger(uint64_t nb_right_bits) const
{
    Integer ret_value = 0;
    uint64_t i_end = min(this->nbElements(), nb_right_bits/this->elemValueBitSize());
    for(uint64_t i=0;i<i_end;i++)
        ret_value += (Integer(getElem(this->nbElements()-1-i)) << (i*this->getElemBitSize()));
    return ret_value;     
}

/********************************************* byteSetView *********************************************/

