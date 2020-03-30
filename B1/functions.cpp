#include "functions.hpp"


void shreder::fillRandom(double *array, int size)
{
  for (int i = 0; i < size; ++i)
  {
    array[i] = (rand() % 21 - 10) / 10.0;
  }
}
