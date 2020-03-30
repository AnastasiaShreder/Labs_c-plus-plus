#include "tasks.hpp"
#include <list>

const int MAX = 20;
const int MIN = 1;
const int MAX_LENGTH = 20;

void print(std::list<int> &list)
{
  if (list.empty())
  {
    return;
  }

  std::list<int>::const_iterator firstIter = list.cbegin();
  std::list<int>::const_iterator lastIter = list.cend();
  --lastIter;

  for (size_t i = 0; i < list.size()/2; ++i)
  {
    if (i > 0)
    {
      std::cout << " ";
    }
    std::cout << *firstIter << " " << *lastIter;
    ++firstIter;
    --lastIter;
  }
  if (list.size() % 2 == 1)
  {
    if (list.size() > 1)
    {
      std::cout << " ";
    }
    std::cout << *firstIter;
  }
  std::cout <<std::endl;
}


void shreder::task2()
{
  std::list<int> list;
  int elem = 0;
  while (std::cin && !(std::cin >> elem).eof())
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("There is an error during reading the file\n");
    }
    if ((elem < MIN) || (elem > MAX))
    {
      throw std::invalid_argument("Element must be between 1 and 20\n");
    }

    list.push_back(elem);

    if (list.size() > MAX_LENGTH)
    {
      throw std::invalid_argument("The size of the list is overflowed\n");
    }
  }

  print(list);
}

