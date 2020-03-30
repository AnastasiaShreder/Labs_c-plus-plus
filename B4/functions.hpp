#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "dataStruct.hpp"
#include <vector>

namespace shreder
{
  std::vector<shreder::DataStruct> readVector();
  bool compare(const shreder::DataStruct &, const shreder::DataStruct &);
}

#endif
