#ifndef B3_FACTORIAL_HPP
#define B3_FACTORIAL_HPP

#include <iterator>

class Factorial
{
public:
  class FactorialIterator : public std::iterator<std::bidirectional_iterator_tag, std::size_t>
  {
  public:
    FactorialIterator();
    FactorialIterator(std::size_t);

    std::size_t getFactorial(std::size_t) const;

    std::size_t operator ->() const;
    std::size_t operator *() const;

    FactorialIterator &operator ++();
    const FactorialIterator operator ++(int);
    FactorialIterator &operator --();
    const FactorialIterator operator --(int);

    bool operator ==(const FactorialIterator&) const;
    bool operator !=(const FactorialIterator&) const;
  private:
    std::size_t number_;
  };

  Factorial() = default;
  ~Factorial() = default;
  FactorialIterator begin();
  FactorialIterator end();
};

#endif
