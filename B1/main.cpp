#include <iostream>
#include <ctime>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  srand(time(nullptr));
  if ((argc < 2) || (argc > 4))
  {
    std::cerr << "Incorrect number of parameters";
    return 1;
  }

  try
  {
    switch (atoi(argv[1]))
    {
      case 1:
        if (argc != 3)
        {
          std::cerr << "Incorrect number of parameters\n";
          return 1;
        }
        shreder::task1(argv[2]);
        break;

      case 2:
        if (argc != 3)
        {
          std::cerr << "Incorrect number of parameters\n";
          return 1;
        }
        shreder::task2(argv[2]);
        break;

      case 3:
        shreder::task3();
        break;

      case 4:
        if (argc != 4)
        {
          std::cerr << "Incorrect number of parameters\n";
          return 1;
        }
        shreder::task4(argv[2], argv[3]);
        break;

      default:
        std::cerr << "Invalid number of task\n";
        return 1;
    }
  }

  catch(const std::exception &error)
  {
    std::cerr << error.what();
    return 1;
  }

  return 0;
}