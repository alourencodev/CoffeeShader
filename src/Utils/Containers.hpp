#ifndef COFFEE_UTILS_CONTAINERS_HPP 
#define COFFEE_UTILS_CONTAINERS_HPP 

#include <vector>

namespace coffee::utils
{

template<typename T>
void unorderedRemove(std::vector<T> &v, const typename std::vector<T>::iterator &it)
{
    *it = std::move(v.back());
    v.pop_back();
}

}

#endif