#ifndef STRATIFICATION_HPP
#define STRATIFICATION_HPP

#include "composite-shape.hpp"
#include "matrix.hpp"

namespace shreder
{
  Matrix<Shape> layer(const CompositeShape &);
  bool cross(const Shape &, const Shape &);
}

#endif