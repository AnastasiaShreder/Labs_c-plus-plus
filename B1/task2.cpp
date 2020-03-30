#include "tasks.hpp"
#include <fstream>
#include <memory>
#include <iostream>

const std::size_t INIT_SIZE = 1024;

void shreder::task2(const char *file)
{
  std::ifstream input(file);
  if (!input)
  {
    throw std::invalid_argument("File does not exist");
  }

  std::size_t sizeOfArray = INIT_SIZE;
  typedef std::unique_ptr<char[], decltype(&free)> arrayOfChars;
  arrayOfChars array(static_cast<char *>(malloc(sizeOfArray)), &free);

  std::size_t size = 0;//size

  while (input)
  {
    input.read(&array[size], INIT_SIZE);
    size += input.gcount();
    if (input.gcount() == INIT_SIZE)
    {
      sizeOfArray += INIT_SIZE;
      arrayOfChars tempArray(static_cast<char *>(realloc(array.get(), sizeOfArray)), &free);
      array.release();
      std::swap(array, tempArray);
    }
    if (!input.eof() && input.fail())
    {
      throw std::runtime_error("There is error during reading the file");
    }
  }

  std::vector<char> vect(&array[0], &array[size]);

  for (char i : vect) //standart cicle
  {
    std::cout << i;
  }

}
