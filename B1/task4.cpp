#include "tasks.hpp"
#include "functions.hpp"

void shreder::task4(const char *direction, const char *size)
{
  auto compare = getDirection<double>(direction);

  int vectSize = atoi(size);

  if (vectSize <= 0)
  {
    throw std::invalid_argument("Size must not be negative or zero");
  }

  std::vector<double> vect(vectSize);
  fillRandom(vect.data(), vectSize);
  printContainer(vect);
  sort<accessWithAt>(vect, compare);
  printContainer(vect);
}
