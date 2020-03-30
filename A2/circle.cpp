#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

shreder::Circle::Circle(const point_t & center, const double radius):
        center_(center),
        radius_(radius)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Radius must not be zero or negative");
  }
}
double shreder::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}
shreder::rectangle_t shreder::Circle::getFrameRect() const
{
  return {center_, 2 * radius_, 2 * radius_};
}
void shreder::Circle::move(const double moveX, const double moveY)
{
  center_.x += moveX;
  center_.y += moveY;
}
void shreder::Circle::move(const point_t & new_center)
{
  center_ = new_center;
}
void shreder::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient must not be zero or negative");
  }
  radius_ *= coefficient;
}

void shreder::Circle::printInf() const
{
  std::cout << "Center of the circle is (" << center_.x << "," << center_.y << ")\n";
  std::cout << "Radius of the circle is " << radius_ << "\n";
  std::cout << "Area of the circle is " << getArea() << "\n";
  std::cout << "Parameters of the frame rectangle: " << "\n";
  std::cout << "Width: " << getFrameRect().width << "\n";
  std::cout << "Height: " << getFrameRect().height << "\n";
  std::cout << "Coordinates of center: (" << getFrameRect().pos.x << "," << getFrameRect().pos.y << ")\n";
}
