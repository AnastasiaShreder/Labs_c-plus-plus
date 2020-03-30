#include <iostream>
#include <sstream>
#include "functions.hpp"

const int MAX = 5;
const int MIN = -5;

std::vector<shreder::DataStruct> shreder::readVector()
{
  std::vector<DataStruct> vector;

  int key1 = 0;
  int key2 = 0;

  std::string string;
  std::string data;
  std::string line;

  while (std::getline(std::cin >> std::ws, line))
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("There is an error during reading the file\n");
    }

    std::size_t comma = line.find_first_of(',');
    if (comma == std::string::npos)
    {
      throw std::invalid_argument("Incorrect data");
    }
    key1 = std::stoi(line.substr(0, comma));
    line.erase(0, comma + 1);

    comma = line.find_first_of(',');
    if (comma == std::string::npos)
    {
      throw std::invalid_argument("Incorrect data");
    }

    key2 = std::stoi(line.substr(0, comma));
    line.erase(0, comma + 1);

    if (key1 < MIN || key1 > MAX || key2 < MIN || key2 > MAX)
    {
      throw std::out_of_range("Incorrect key value");
    }

    if (line.empty())
    {
      throw std::invalid_argument("Incorrect data");
    }

    vector.push_back({key1, key2, line});
  }
  return vector;
}

bool shreder::compare(const shreder::DataStruct &struct1, const shreder::DataStruct &struct2)
{
  if (struct1.key1 < struct2.key1)
  {
    return true;
  }

  if (struct1.key1 == struct2.key1)
  {
    if (struct1.key2 == struct2.key2)
    {
      if (struct1.str.size() == struct2.str.size())
      {
        return (struct1.str < struct2.str);
      }
      return (struct1.str.size() < struct2.str.size());
    }
    return (struct1.key2 < struct2.key2);
  }
  return false;
}
