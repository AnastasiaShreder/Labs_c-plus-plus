#include "factorial.hpp"

const std::size_t MAX_INDEX = 11;
const std::size_t MIN_INDEX = 1;

Factorial::FactorialIterator::FactorialIterator() :
        FactorialIterator(1)
{
}

Factorial::FactorialIterator::FactorialIterator(std::size_t number) :
        number_(number)
{
}

std::size_t Factorial::FactorialIterator::getFactorial(std::size_t number) const
{
  std::size_t result = 1;
  for (std::size_t i = 1; i <= number; ++i)
  {
    result *= i;
  }

  return result;
}

std::size_t Factorial::FactorialIterator::operator ->() const
{
  return getFactorial(number_);
}

std::size_t Factorial::FactorialIterator::operator *() const
{
  return getFactorial(number_);
}

Factorial::FactorialIterator &Factorial::FactorialIterator::operator ++()
{
  if(number_ < MAX_INDEX)
  {
    ++number_;
  }
  return *this;
}

const Factorial::FactorialIterator Factorial::FactorialIterator::operator ++(int)
{
  Factorial::FactorialIterator tmp = *this;
  ++(*this);
  return tmp;
}

Factorial::FactorialIterator &Factorial::FactorialIterator::operator --()
{
  if(number_ > MIN_INDEX)
  {
    --number_;
  }
  return *this;
}

const Factorial::FactorialIterator Factorial::FactorialIterator::operator --(int)
{
  Factorial::FactorialIterator tmp = *this;
  --(*this);
  return tmp;
}

bool Factorial::FactorialIterator::operator ==(const Factorial::FactorialIterator &rhs) const
{
  return (number_ == rhs.number_);
}

bool Factorial::FactorialIterator::operator !=(const Factorial::FactorialIterator &rhs) const
{
  return (number_ != rhs.number_);
}

Factorial::FactorialIterator Factorial::begin()
{
  return FactorialIterator(MIN_INDEX);
}

Factorial::FactorialIterator Factorial::end()
{
  return FactorialIterator(MAX_INDEX);
}

