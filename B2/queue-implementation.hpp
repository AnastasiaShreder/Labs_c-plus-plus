#ifndef QUEUE_IMPLEMENTATION_HPP
#define QUEUE_IMPLEMENTATION_HPP

#include "queue-interface.hpp"
#include <stdexcept>

template<typename ElementType>
void shreder::QueueWithPriority <ElementType>::putElementToQueue(const ElementType &element, shreder::ElementPriority priority)
{
  switch (priority)
  {
    case shreder::ElementPriority::LOW:
      low_.push_back(element);
      break;

    case shreder::ElementPriority::NORMAL:
      normal_.push_back(element);
      break;

    case shreder::ElementPriority::HIGH:
      high_.push_back(element);
      break;

    default:
      throw std::invalid_argument("Incorrect priority\n");
  }
}

template<typename ElementType>
ElementType shreder::QueueWithPriority<ElementType>::getElementFromQueue()
{
  if (!high_.empty())
  {
    ElementType element = high_.front();
    high_.pop_front();
    return element;
  }
  else if (!normal_.empty())
  {
    ElementType element = normal_.front();
    normal_.pop_front();
    return element;
  }
  else
  {
    ElementType element = low_.front();
    low_.pop_front();
    return element;
  }
}

template<typename ElementType>
void shreder::QueueWithPriority<ElementType>::accelerate()
{
  high_.splice(high_.end(), low_);
}

template<typename ElementType>
bool shreder::QueueWithPriority<ElementType>::empty() const
{
  return high_.empty() && normal_.empty() && low_.empty();
}


#endif
