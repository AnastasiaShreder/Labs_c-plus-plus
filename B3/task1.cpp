#include "tasks.hpp"
#include "phone-book.hpp"
#include "interface.hpp"

int shreder::task1()
{
  PhoneBook phoneBook;
  Interface phoneBookInterface(phoneBook);
  std::string line;
  std::stringstream string;

  while (std::getline(std::cin, line))
  {
    string.clear();
    string.str(line);
    if (std::cin.fail())
    {
      return 2;
    }
    if (std::cin.eof())
    {
      break;
    }
    phoneBookInterface.chooseCommand(string);
  }
  return 0;
}

