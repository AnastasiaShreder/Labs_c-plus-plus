#include <algorithm>
#include <iostream>
#include "dataStruct.hpp"
#include "functions.hpp"

int main()
{
  try
  {
    std::vector<shreder::DataStruct> vect = shreder::readVector();
    if (vect.size() > 1)
    {
      std::sort(vect.begin(), vect.end(), shreder::compare);
    }
    if (!vect.empty())
    {
      for (const auto &vector: vect)
      {
        std::cout << vector.key1 << ',' << vector.key2 << ',' << vector.str << '\n';
      }
    }
  }

  catch (const std::exception &err)
  {
    std::cerr << err.what();
    return 1;
  }
  return 0;
}
