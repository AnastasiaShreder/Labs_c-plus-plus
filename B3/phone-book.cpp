#include "phone-book.hpp"

shreder::PhoneBook::PhoneBook()
{
  bookmarks_.emplace_back(records_.end(), "current");
  actualBookmark_ = bookmarks_.begin();
}

shreder::PhoneBook::record &shreder::PhoneBook::getRecord() const
{
  return *(actualBookmark_->first);
}

void shreder::PhoneBook::addMark(const std::string &name)
{
  bookmarks_.emplace_back(actualBookmark_->first, name);
}

bool shreder::PhoneBook::makeMarkActual(const std::string &mark)
{
  for (bookmarkIter it = bookmarks_.begin(); it != bookmarks_.end(); ++it)
  {
    if (it->second == mark)
    {
      actualBookmark_ = it;
      return true;
    }
  }
  std::cout << "<INVALID BOOKMARK>\n";
  return false;
}

/*void shreder::PhoneBook::store(const std::string &markName, const std::string &newMarkName)
{
  if (!makeMarkActual(markName))
  {
    return;
  }
  addMark(newMarkName);
}*/

/*void shreder::PhoneBook::next()
{
  std::size_t dist = std::distance(records_.begin(), actualBookmark_->first);//??
  if (dist >= records_.size())
  {
    return;
  }
  else
  {
    actualBookmark_->first++;
  }
}*/

/*void shreder::PhoneBook::prev()
{
  std::size_t dist = std::distance(records_.begin(), actualBookmark_->first);
  if (dist <= 0)
  {
    return;
  }
  else
  {
    actualBookmark_->first--;
  }
}*/

void shreder::PhoneBook::insertBefore(const std::string &name, const std::string &phoneNumber, const std::string &markName)
{
  if (!makeMarkActual(markName))
  {
    return;
  }
  if (actualBookmark_->first == records_.end())
  {
    records_.emplace_back(name, phoneNumber);
    actualBookmark_->first--;
  }
  else
  {
    records_.emplace(actualBookmark_->first, name, phoneNumber);
  }
}

void shreder::PhoneBook::insertAfter(const std::string &name, const std::string &phoneNumber, const std::string &markName)
{
  if (!makeMarkActual(markName))
  {
    return;
  }
  if (actualBookmark_->first == records_.end())
  {
    records_.emplace_back(name, phoneNumber);
    actualBookmark_->first--;
  }
  else
  {
    records_.emplace(std::next(actualBookmark_->first), name, phoneNumber);
  }
}

void shreder::PhoneBook::removeRecord(const std::string &markName)
{
  if (!makeMarkActual(markName))
  {
    return;
  }

  iter ourRecord = actualBookmark_->first;

  for (bookmarkIter bookIter = bookmarks_.begin(); bookIter != bookmarks_.end(); ++bookIter)
  {
    if (bookIter->first == ourRecord)
    {
      if ((bookIter->first == std::prev(records_.end())) && (records_.size() > 1))
      {
        bookIter->first--;
      }
      else
      {
        bookIter->first++;
      }
    }
  }
  records_.erase(ourRecord);
}

/*void shreder::PhoneBook::changeRecord(const std::string &name, const std::string &phoneNumber)
{
  if ((actualBookmark_->first == records_.end()) && (records_.size() > 1))
  {
    removeRecord();
    insertAtTheEnd(name, phoneNumber);
  }
  else
  {
    removeRecord();
    insertBefore(name, phoneNumber);
  }
}*/

void shreder::PhoneBook::insertAtTheEnd(const std::string &name, const std::string &phoneNumber)
{
  records_.emplace_back(name, phoneNumber);
  if (actualBookmark_->first == records_.end())
  {
    actualBookmark_->first--;
  }
}

void shreder::PhoneBook::move(const std::string &steps, const std::string &markName)
{
  if (!makeMarkActual(markName))
  {
    return;
  }
  if (steps == "first")
  {
    actualBookmark_->first = records_.begin();
    return;
  }
  if (steps == "last")
  {
    actualBookmark_->first = std::prev(records_.end());
    return;
  }

  std::istringstream string(steps);
  int distance = 0;

  string >> distance;

  if (string.fail())
  {
    std::cout << "<INVALID STEP>\n";
  }

  int minDistance = distance + std::distance(records_.begin(), actualBookmark_->first);
  unsigned int maxDistance = static_cast<unsigned int>(distance + std::distance(records_.begin(), actualBookmark_->first));
  if ((minDistance < 0) || (maxDistance >= records_.size()))
  {
    return;
  }

  std::advance(actualBookmark_->first, distance);
}

bool shreder::PhoneBook::empty() const
{
  return records_.empty();
}
