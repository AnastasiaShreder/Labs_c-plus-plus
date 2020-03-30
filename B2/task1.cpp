#include "tasks.hpp"
#include "queue-implementation.hpp"
#include <string>
#include <sstream>
#include <algorithm>
#include "functions.hpp"

void shreder::task1()
{
  QueueWithPriority<std::string> queue;
  std::string line;
  std::string command;
  std::string priority;
  std::string data;
  std::stringstream string;

  while (std::getline(std::cin >> std::ws, line))
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("There is an error during reading\n");
    }

    string.clear();
    string.str(line);
    string >> std::ws >> command;

    if (command == "add")
    {
      string >> std::ws >> priority;
      transform(priority.begin(), priority.end(), priority.begin(), tolower);
      std::getline(string >> std::ws, data);

      add(queue, priority, data);
    }
    else if (command == "get")
    {
      get(queue);
    }
    else if (command == "accelerate")
    {
      accelerate(queue);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
