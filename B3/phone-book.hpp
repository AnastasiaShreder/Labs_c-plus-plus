#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <utility>
#include <string>
#include <list>
#include <sstream>
#include <iostream>

namespace shreder
{
  class PhoneBook
  {
  public:

  typedef std::pair<std::string, std::string> record;
  typedef std::list<record>::iterator iter;
  typedef std::list<std::pair<iter, std::string>> bookmark;
  typedef bookmark::iterator bookmarkIter;

  PhoneBook();
  ~PhoneBook() = default;
  record &getRecord() const;
  void addMark(const std::string &);
  bool makeMarkActual(const std::string &);
//  void store(const std::string &, const std::string &);
  void insertBefore(const std::string &, const std::string &, const std::string &);
  void insertAfter(const std::string &, const std::string &, const std::string &);
  void removeRecord(const std::string &);
//  void changeRecord(const std::string &, const std::string &);
  void insertAtTheEnd(const std::string &, const std::string &);
  void move(const std::string &, const std::string &);
 // void next();
 // void prev();
  bool empty() const;

private:
  std::list<record> records_;
  bookmark bookmarks_;
  bookmarkIter actualBookmark_;
};
}
#endif
