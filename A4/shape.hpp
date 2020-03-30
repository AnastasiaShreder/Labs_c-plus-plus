#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
#include <memory>

namespace shreder
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &) = 0;
    virtual void move(double, double) = 0;
    virtual void scale(double) = 0;
    virtual void rotate(double) = 0;
    //virtual double sine(double) const = 0;
    //virtual double cosine(double) const = 0;
    virtual void printInf() const = 0;
  };
  using shape_ptr = std::shared_ptr<Shape>;
  using array_ptr = std::unique_ptr<shape_ptr[]>;
 }

#endif /*SHAPE_HPP*/
