#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

shreder::Rectangle::Rectangle(const point_t & center, const double width, const double height):
        center_(center),
        width_(width),
        height_(height)
{
  if (width_ <= 0)
  {
    throw std::invalid_argument("Width must not be zero or negative");
  }
  if (height_ <= 0)
  {
    throw std::invalid_argument("Height must not be zero or negative");
  }
}
double shreder::Rectangle::getArea() const
{
  return width_ * height_;
}
shreder::rectangle_t shreder::Rectangle::getFrameRect() const
{
  return {center_, width_, height_};
}
void shreder::Rectangle::move(const double moveX, const double moveY)
{
  center_.x += moveX;
  center_.y += moveY;
}
void shreder::Rectangle::move(const point_t & new_center)
{
  center_ = new_center;
}
void shreder::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient must not be zero or negative");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void shreder::Rectangle::printInf() const
{
  std::cout << "Center of the rectangle is (" << center_.x << "," << center_.y << ")\n";
  std::cout << "Width of the rectangle is " << width_ << "\n";
  std::cout << "Height of the rectangle is " << height_ << "\n";
  std::cout << "Area of the rectangle is " << getArea() << "\n";
  std::cout << "Parameters of the frame rectangle: " << "\n";
  std::cout << "Width: " << getFrameRect().width << "\n";
  std::cout << "Height: " << getFrameRect().height << "\n";
  std::cout << "Coordinates of center: (" << getFrameRect().pos.x << "," << getFrameRect().pos.y << ")\n";
}
