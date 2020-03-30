#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "phone-book.hpp"

class Interface
{
public:
  Interface(shreder::PhoneBook &);
  ~Interface() = default;
  void chooseCommand(std::istream &);
  void add(std::istream &);
  void store(std::istream &);
  void insert(std::istream &);
  void delet(std::istream &);
  void show(std::istream &);
  void move(std::istream &);
  void makeHumanReadable(std::string &);
private:
  shreder::PhoneBook &phoneBook_;
  Interface() = delete;
};

#endif
