#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace shreder
{
class Triangle : public Shape
  {
  public:
  Triangle(const point_t &, const point_t &, const point_t &);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &) override;
  void move(const double, const double) override;
  void scale(double) override;
  void rotate(double) override;
  double sine(double) const;
  double cosine(double) const;
  void printInf() const override;

private:
  point_t center_;
  point_t pointA_;
  point_t pointB_;
  point_t pointC_;
  };
}

#endif
