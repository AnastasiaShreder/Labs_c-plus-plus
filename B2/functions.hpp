#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "tasks.hpp"
#include "queue-implementation.hpp"

namespace shreder
{
void add(QueueWithPriority<std::string> &queue, const std::string &priority, const std::string &data);
void get(QueueWithPriority<std::string> &queue);
void accelerate(QueueWithPriority<std::string> &queue);
}

#endif



