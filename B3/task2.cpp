#include <iostream>
#include <algorithm>
#include "tasks.hpp"
#include "factorial.hpp"

int shreder::task2()
{
  Factorial factorial;
  typedef std::ostream_iterator<std::size_t> stream;

  std::copy(factorial.begin(), factorial.end(), stream(std::cout, " "));
  std::cout << '\n';

  std::copy(factorial.begin(), factorial.end(), stream(std::cout, " "));
  std::cout << '\n';

  return 0;
}

