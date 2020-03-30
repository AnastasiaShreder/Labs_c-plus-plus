#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "access.hpp"
#include <functional>
#include <iostream>
#include <cstring>

namespace shreder
{

void fillRandom(double *array, int size);

template<typename ContainerType>
std::function<bool(ContainerType, ContainerType)> getDirection(const char *direction)
{
  if (!std::strcmp(direction, "ascending"))
  {
    return std::function<bool(ContainerType, ContainerType)>(std::greater<ContainerType>());
  }
  if (!std::strcmp(direction, "descending"))
  {
    return std::function<bool(ContainerType, ContainerType)>(std::less<ContainerType>());
  }
  throw std::invalid_argument("Invalid sorting direction");
}

template<template<class Container> class Access, class Container>
void sort(Container &cont, std::function<bool(typename Container::value_type, typename Container::value_type)> compare)
{
  typedef class Access<Container> containerAccess;
  const auto begin = containerAccess::getBegin(cont);
  const auto end = containerAccess::getEnd(cont);

  for (auto i = begin; i != end; ++i)
  {
    for (auto k = containerAccess::nextElem(i); k != end; ++k)
    {
      if (compare(containerAccess::getElement(cont, i), containerAccess::getElement(cont, k)))
      {
        std::swap(containerAccess::getElement(cont, i), containerAccess::getElement(cont, k));
      }
    }
  }
}

template<class Container>
void printContainer(const Container &cont)
{
  if (cont.empty())
  {
    return;
  }
  for (const auto element: cont)
  {
    std::cout << element << " ";
  }
  std::cout << '\n';
}

}

#endif