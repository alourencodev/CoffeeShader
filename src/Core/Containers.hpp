#ifndef COFFEE_UTILS_CONTAINERS_HPP 
#define COFFEE_UTILS_CONTAINERS_HPP 

#include <vector>

namespace coffee
{

template<typename T, size_t columns, size_t rows>
class matrix
{
public:
    T *data() const { return &_data[0][0]; }
    std::array<T, columns> &operator[](std::size_t index) { return _data[index]; }
    T &at(std::size_t column, std::size_t row) { return _data[column][row]; }

private:
    std::array<std::array<T, columns>, rows> _data;
};

namespace utils
{

template<typename T>
void unorderedRemove(std::vector<T> &v, const typename std::vector<T>::iterator &it)
{
    *it = std::move(v.back());
    v.pop_back();
}

}

}

#endif