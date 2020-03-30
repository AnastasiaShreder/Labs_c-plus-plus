#include "functions.hpp"

namespace shreder
{
void add(QueueWithPriority<std::string> &queue, const std::string &priority, const std::string &data)
{
  if (data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
  }

  if (priority == "high")
  {
    queue.putElementToQueue(data, ElementPriority::HIGH);
  }
  else if (priority == "normal")
  {
    queue.putElementToQueue(data, ElementPriority::NORMAL);
  }
  else if (priority == "low")
  {
    queue.putElementToQueue(data, ElementPriority::LOW);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

void get(QueueWithPriority<std::string> &queue)
{
  if(queue.empty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    std::cout << queue.getElementFromQueue() << '\n';
  }
}

void accelerate(QueueWithPriority<std::string> &queue)
{
  if (queue.empty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    queue.accelerate();
  }
}
}
