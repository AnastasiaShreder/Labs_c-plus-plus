#include <iostream>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Incorrect number of parameters";
      return 1;
    }

    switch (atoi(argv[1]))
    {
      case 1:
        shreder::task1();
        break;

      case 2:
        shreder::task2();
        break;

      default:
        std::cerr << "Invalid number of task";
        return 1;
    }
  }

  catch (const std::exception &err)
  {
    std::cerr << err.what();
    return 1;
  }

  return 0;
}
