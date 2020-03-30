#include "tasks.hpp"
#include "functions.hpp"

void shreder::task3()
{
  std::vector<int> vect;
  int currElement = -1;
  while (std::cin && !(std::cin >> currElement).eof())
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("There is error during reading the file");
    }
    if (currElement == 0)
    {
      break;
    }
    vect.push_back(currElement);
  }

  if (vect.empty())
  {
    return;
  }

  if (currElement != 0)
  {
    throw std::invalid_argument("Last character must be 0");
  }

  std::vector<int>::iterator it = vect.end() - 1; //auto
  switch (*it)
  {
    case 1:
      for (it = vect.begin(); it != vect.end(); ++it)
      {
        if (*it % 2 == 0)
        {
          it = vect.erase(it);
          --it;
        }
      }
      break;
    case 2:
      for (it = vect.begin(); it != vect.end(); ++it)
      {
        if (*it % 3 == 0)
        {
          it = vect.insert(++it, 3, 1);
          it += 2;
        }
      }
      break;
    default:
      break;
  }
  printContainer(vect);
}
