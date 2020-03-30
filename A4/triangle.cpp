#include "triangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

shreder::Triangle::Triangle(const point_t & pointA, const point_t & pointB, const point_t & pointC):
  center_({(pointA.x + pointB.x + pointC.x) / 3, (pointA.y + pointB.y + pointC.y) / 3}),
  pointA_(pointA),
  pointB_(pointB),
  pointC_(pointC)
{
  if (((pointA_.x == pointB_.x) && (pointA_.y == pointB_.y)) || ((pointA_.x == pointC_.x) && (pointA_.y == pointC_.y))
    || ((pointB_.x == pointC_.x) && (pointB_.y == pointC_.y)))
  {
    throw std::invalid_argument("Incorrect parameters of triangle");
  }
}
double shreder::Triangle::getArea() const
{
  return (std::abs((pointB_.x - pointA_.x) * (pointC_.y - pointA_.y) - (pointC_.x - pointA_.x) * (pointB_.y - pointA_.y)) / 2);
}

shreder::rectangle_t shreder::Triangle::getFrameRect() const
{
  const double maxX = std::fmax(std::fmax(pointA_.x, pointB_.x), pointC_.x);
  const double minX = std::fmin(std::fmin(pointA_.x, pointB_.x), pointC_.x);
  const double maxY = std::fmax(std::fmax(pointA_.y, pointB_.y), pointC_.y);
  const double minY = std::fmin(std::fmin(pointA_.y, pointB_.y), pointC_.y);
  return {{(maxX + minX) / 2, (maxY + minY) / 2}, maxX - minX, maxY - minY};
}

void shreder::Triangle::move(const point_t & new_center)
{
  const double moveX = new_center.x - center_.x;
  const double moveY = new_center.y - center_.y;
  move(moveX, moveY);
  center_ = new_center;
}

void shreder::Triangle::move(const double moveX, const double moveY)
{
  center_.x += moveX;
  center_.y += moveY;

  pointA_.x += moveX;
  pointA_.y += moveY;

  pointB_.x += moveX;
  pointB_.y += moveY;

  pointC_.x += moveX;
  pointC_.y += moveY;
}

void shreder::Triangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient must not be zero or negative");
  }
  pointA_.x = center_.x * (1 - coefficient) + pointA_.x * coefficient;
  pointA_.y = center_.y * (1 - coefficient) + pointA_.y * coefficient;
  pointB_.x = center_.x * (1 - coefficient) + pointB_.x * coefficient;
  pointB_.y = center_.y * (1 - coefficient) + pointB_.y * coefficient;
  pointC_.x = center_.x * (1 - coefficient) + pointC_.x * coefficient;
  pointC_.y = center_.y * (1 - coefficient) + pointC_.y * coefficient;
}

void shreder::Triangle::rotate(double angle)
{
  const double Ax = (pointA_.x - center_.x) * cosine(angle) - (pointA_.y - center_.y) * sine(angle);
  const double Ay = (pointA_.x - center_.x) * sine(angle) + (pointA_.y - center_.y) * cosine(angle);
  const double Bx = (pointB_.x - center_.x) * cosine(angle) - (pointB_.y - center_.y) * sine(angle);
  const double By = (pointB_.x - center_.x) * sine(angle) + (pointB_.y - center_.y) * cosine(angle);
  const double Cx = (pointC_.x - center_.x) * cosine(angle) - (pointC_.y - center_.y) * sine(angle);
  const double Cy = (pointC_.x - center_.x) * sine(angle) + (pointC_.y - center_.y) * cosine(angle);
  pointA_.x = Ax + center_.x;
  pointA_.y = Ay + center_.y;
  pointB_.x = Bx + center_.x;
  pointB_.y = By + center_.y;
  pointC_.x = Cx + center_.x;
  pointC_.y = Cy + center_.y;
}

double shreder::Triangle::sine(double angle) const
{
  return std::abs(std::sin(angle * M_PI / 180));
}
double shreder::Triangle::cosine(double angle) const
{
  return std::abs(std::cos(angle * M_PI / 180));
}

void shreder::Triangle::printInf() const
{
  std::cout << "Center of the triangle is (" << center_.x << "," << center_.y << ")\n";
  std::cout << "Coordinates of the tops of triangle are " << "\n";
  std::cout << "A(" << pointA_.x << ", " << pointA_.y << ")" << "\n";
  std::cout << "B(" << pointB_.x << ", " << pointB_.y << ")" << "\n";
  std::cout << "C(" << pointC_.x << ", " << pointC_.y << ")" << "\n";
  std::cout << "Area of the triangle is " << getArea() << "\n";
  std::cout << "Parameters of the frame rectangle: " << "\n";
  std::cout << "Width: " << getFrameRect().width << "\n";
  std::cout << "Height: " << getFrameRect().height << "\n";
  std::cout << "Coordinates of center: (" << getFrameRect().pos.x << "," << getFrameRect().pos.y << ")\n";
}