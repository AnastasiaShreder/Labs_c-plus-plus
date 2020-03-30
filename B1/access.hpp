#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <cstddef>
#include <iterator>

namespace shreder
{
template <typename Container>
struct accessWithBrackets
{
  static typename Container::reference getElement(Container &elem, std::size_t index)
  {
    return elem[index];
  }
  static std::size_t getBegin(const Container &)
  {
    return 0;
  }
  static std::size_t getEnd(const Container &elem)
  {
    return elem.size();
  }
  static std::size_t nextElem(std::size_t index)
  {
    return ++index;
  }
};

template <typename Container>
struct accessWithAt
{
  static typename Container::reference getElement(Container &elem, std::size_t index)
  {
    return elem.at(index);
  }
  static std::size_t getBegin(const Container &)
  {
    return 0;
  }
  static std::size_t getEnd(const Container &elem)
  {
    return elem.size();
  }
  static std::size_t nextElem(std::size_t index)
  {
    return ++index;
  }
};
template <typename Container>
struct accessWithIterator
{
  static typename Container::reference getElement(Container &, typename Container::iterator iter)
  {
    return *iter;
  }
  static typename Container::iterator getBegin(Container &elem)
  {
    return elem.begin();
  }
  static typename Container::iterator getEnd(Container &elem)
  {
    return elem.end();
  }
  static typename Container::iterator nextElem(typename Container::iterator iter)
  {
    return ++iter;
  }
};
}

#endif