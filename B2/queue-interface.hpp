#ifndef QUEUE_INTERFACE_HPP
#define QUEUE_INTERFACE_HPP

#include <list>

namespace shreder
{
  typedef enum
  {
    LOW,
    NORMAL,
    HIGH
  } ElementPriority;

  template <typename ElementType>
  class QueueWithPriority
  {
  public:
    QueueWithPriority() = default;
    ~QueueWithPriority() = default;

    void putElementToQueue(const ElementType &element, shreder::ElementPriority priority);
    ElementType getElementFromQueue();
    void accelerate();
    bool empty() const;

  private:
    std::list<ElementType> high_;
    std::list<ElementType> normal_;
    std::list<ElementType> low_;
  };
}
#endif
