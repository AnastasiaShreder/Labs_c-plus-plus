#include "tasks.hpp"
#include "functions.hpp"
#include <forward_list>

void shreder::task1(const char *direction)
{
  auto compare = getDirection<int>(direction);

  std::vector<int> vectWithBrackets;
  int currElement = -1;
  while (std::cin && !(std::cin >> currElement).eof())
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("There is an error during reading the file\n");
    }
    vectWithBrackets.push_back(currElement);
  }
  std::vector<int> vectWithAt(vectWithBrackets);
  std::forward_list<int> list(vectWithAt.begin(), vectWithAt.end());

  sort<accessWithBrackets>(vectWithBrackets, compare);
  printContainer(vectWithBrackets);

  sort<accessWithAt>(vectWithAt, compare);
  printContainer(vectWithAt);

  sort<accessWithIterator>(list, compare);
  printContainer(list);
}
