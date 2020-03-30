#include <iostream>
#include "interface.hpp"

Interface::Interface(shreder::PhoneBook &phoneBook) :
        phoneBook_(phoneBook)
{
}

void Interface::chooseCommand(std::istream &input)
{
  std::string command;
  input >> command;
  if (command.empty())
  {
    return;;
  }
  else if (command == "add")
  {
    add(input);
  }
  else if (command == "store")
  {
    store(input);
  }
  else if (command == "insert")
  {
    insert(input);
  }
  else if (command == "delete")
  {
    delet(input);
  }
  else if (command == "show")
  {
    show(input);
  }
  else if (command == "move")
  {
    move(input);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

void Interface::add(std::istream &input)
{
  std::string phoneNumber;
  input >> phoneNumber;
  std::string name;
  input.ignore();
  std::getline(input, name);

  if ((name.empty()) || (phoneNumber.empty()))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  if ((name.front() != '"') || (name.back() != '"'))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  makeHumanReadable(name);

  phoneBook_.insertAtTheEnd(name, phoneNumber);
}

void Interface::store(std::istream &input)
{
  std::string markName;
  std::string newMarkName;
  input >> markName >> newMarkName;

  if ((markName.empty()) || (newMarkName.empty()))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  if (!phoneBook_.makeMarkActual(markName))
  {
    return;
  }

  phoneBook_.addMark(newMarkName);
}

void Interface::insert(std::istream &input)
{
  std::string position;
  std::string mark;
  std::string phoneNumber;
  input >> position >> mark >> phoneNumber;
  std::string name;
  input.ignore();
  std::getline(input, name);

  if ((position.empty()) || (mark.empty()) || (phoneNumber.empty()) || (name.empty()))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  if ((name.front() != '"') || (name.back() != '"'))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  makeHumanReadable(name);

  if (position == "before")
  {
    phoneBook_.insertBefore(name, phoneNumber, mark);
  }
  else if(position == "after")
  {
    phoneBook_.insertAfter(name, phoneNumber, mark);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

void Interface::delet(std::istream &input)
{
  std::string bookMark;
  input >> bookMark;
  phoneBook_.removeRecord(bookMark);
}

void Interface::show(std::istream &input)
{
  std::string bookMark;
  input >> bookMark;
  if (!phoneBook_.makeMarkActual(bookMark))
  {
    return;
  }
  else if (phoneBook_.empty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    std::cout << phoneBook_.getRecord().second << " " << phoneBook_.getRecord().first << '\n';
  }
}

void Interface::move(std::istream &input)
{
  std::string bookMark;
  std::string steps;
  input >> bookMark >> steps;

  phoneBook_.move(steps, bookMark);
}

void Interface::makeHumanReadable(std::string &name)
{
  for (std::size_t i = 0; i < name.size(); ++i)
  {
    if ((name[i] == '\\') && ((name[i + 1] == '"') || (name[i + 1] == '\\')))
    {
      name.erase(i, 1);
    }
    else if (name[i] == '"')
    {
      name.erase(i, 1);
    }
  }
}
