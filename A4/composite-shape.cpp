#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <cmath>

shreder::CompositeShape::CompositeShape():
  count_(0),
  arrOfShapes_(nullptr)
{
}
shreder::CompositeShape::CompositeShape(const shreder::CompositeShape & copyCompositeShape):
  count_(copyCompositeShape.count_),
  arrOfShapes_(std::make_unique<shape_ptr []>(copyCompositeShape.count_))
{
  for (std::size_t i = 0; i < count_; ++i)
  {
    arrOfShapes_[i] = copyCompositeShape.arrOfShapes_[i];
  }
}
shreder::CompositeShape::CompositeShape(shreder::CompositeShape && moveCompositeShape) noexcept:
  count_(moveCompositeShape.count_),
  arrOfShapes_(std::move(moveCompositeShape.arrOfShapes_))
{
  moveCompositeShape.count_ = 0;
}
shreder::CompositeShape::CompositeShape(const shape_ptr & shape):
  count_(1),
  arrOfShapes_(std::make_unique<shape_ptr []>(1))
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("You cannot pass an empty pointer");
  }
  arrOfShapes_[0] = shape;
}
shreder::CompositeShape & shreder::CompositeShape::operator =(const shreder::CompositeShape & copyCompositeShape)
{
  if (this != & copyCompositeShape)
  {
    count_ = copyCompositeShape.count_;
    arrOfShapes_ = std::make_unique<shape_ptr []>(copyCompositeShape.count_);
    for (std::size_t i = 0; i < count_; ++i)
    {
      arrOfShapes_[i] = copyCompositeShape.arrOfShapes_[i];
    }
  }
  return *this;
}
shreder::CompositeShape & shreder::CompositeShape::operator =(shreder::CompositeShape && moveCompositeShape) noexcept
{
  if (this != & moveCompositeShape)
  {
    count_ = moveCompositeShape.count_;
    arrOfShapes_ = std::move(moveCompositeShape.arrOfShapes_);
  }
  return *this;
}
shreder::shape_ptr shreder::CompositeShape::operator [](std::size_t index) const
{
  if (index >= count_ )
  {
    throw std::out_of_range("Incorrect shape index");
  }
  return arrOfShapes_[index];
}
double shreder::CompositeShape::getArea() const
{
  if (count_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  double areaOfShapes = 0.0;
  for (std::size_t i = 0; i < count_ ; ++i)
  {
    areaOfShapes += arrOfShapes_[i]->getArea();
  }
  return areaOfShapes;
}
shreder::rectangle_t shreder::CompositeShape::getFrameRect() const
{
  if (count_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  shreder::rectangle_t actualFrameRectangle = arrOfShapes_[0]->getFrameRect();
  double right = actualFrameRectangle.pos.x + (actualFrameRectangle.width / 2);
  double left = actualFrameRectangle.pos.x - (actualFrameRectangle.width / 2);
  double top = actualFrameRectangle.pos.y + (actualFrameRectangle.height / 2);
  double bottom = actualFrameRectangle.pos.y - (actualFrameRectangle.height / 2);
  for (std::size_t i = 1; i < count_; ++i)
  {
    actualFrameRectangle = arrOfShapes_[i]->getFrameRect();
    right = std::max(actualFrameRectangle.pos.x + (actualFrameRectangle.width / 2), right);
    left = std::min(actualFrameRectangle.pos.x - (actualFrameRectangle.width / 2), left);
    top = std::max(actualFrameRectangle.pos.y + (actualFrameRectangle.height / 2), top);
    bottom = std::min(actualFrameRectangle.pos.y - (actualFrameRectangle.height / 2), bottom);
  }
  return {{(right + left) / 2, (top + bottom) / 2}, right - left, top - bottom};
}
void shreder::CompositeShape::move(double moveX, double moveY)
{
  if (count_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  for (std::size_t i = 0; i < count_; ++i)
  {
    arrOfShapes_[i]->move(moveX, moveY);
  }
}
void shreder::CompositeShape::move(const point_t & new_center)
{
  point_t centerFrameRectangle = getFrameRect().pos;
  double moveX = new_center.x - centerFrameRectangle.x;
  double moveY = new_center.y - centerFrameRectangle.y;
  move(moveX, moveY);
}
void shreder::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient must not be zero or negative");
  }
  point_t centerFrameRectangle = getFrameRect().pos;
  for (std::size_t i = 0; i < count_; ++i)
  {
    point_t centerShape = arrOfShapes_[i]->getFrameRect().pos;
    arrOfShapes_[i]->scale(coefficient);
    double moveX = (centerShape.x - centerFrameRectangle.x) * (coefficient - 1);
    double moveY = (centerShape.y - centerFrameRectangle.y) * (coefficient - 1);
    arrOfShapes_[i]->move(moveX, moveY);
  }
}
void shreder::CompositeShape::rotate(double angle)
{
  const point_t center = getFrameRect().pos;
  for (std::size_t i = 0; i < count_; ++i)
  {
    const point_t centerOfTheShape = arrOfShapes_[i]->getFrameRect().pos;
    const double moveX = centerOfTheShape.x - center.x;
    const double moveY = centerOfTheShape.y - center.y;
    arrOfShapes_[i]->move(moveX * (cosine(angle) - 1) - moveY * sine(angle), moveX * sin(angle) + moveY * (cosine(angle) - 1));
    arrOfShapes_[i]->rotate(angle);
  }
}
void shreder::CompositeShape::add(const shape_ptr & shape)
{
  array_ptr tempArr(std::make_unique<shape_ptr []>(count_ + 1));
  for (std::size_t i = 0; i < count_; ++i)
  {
    tempArr[i] = arrOfShapes_[i];
  }
  tempArr[count_] = shape;
  arrOfShapes_ = std::move(tempArr);
  count_++;
}
void shreder::CompositeShape::remove(size_t index)
{
  if (index >= count_)
  {
    throw std::out_of_range("Incorrect shape index");
  }
  count_--;
  for (std::size_t i = index; i < count_; ++i)
  {
    arrOfShapes_[i] = arrOfShapes_[i + 1];
  }
  arrOfShapes_[count_] = nullptr;
}
std::size_t shreder::CompositeShape::getCount() const
{
  return count_;
}

double shreder::CompositeShape::sine(double angle) const
{
  return std::abs(std::sin(angle * M_PI / 180));
}
double shreder::CompositeShape::cosine(double angle) const
{
  return std::abs(std::cos(angle * M_PI / 180));
}

void shreder::CompositeShape::printInf() const
{
  std::cout << "Center of the composite shape is (" << getFrameRect().pos.x << "," << getFrameRect().pos.y << ")\n";
  std::cout << "Area of the composite shape is " << getArea() << '\n';
  std::cout << "Parameters of the frame rectangle: " << '\n';
  std::cout << "Width: " << getFrameRect().width << '\n';
  std::cout << "Height: " << getFrameRect().height << '\n';
  std::cout << "Count of shapes " << count_ << '\n';
}
