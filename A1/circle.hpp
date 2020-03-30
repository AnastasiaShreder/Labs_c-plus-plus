#include "circle.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

Circle::Circle(const point_t& center, const double radius):
        center_(center),
        radius_(radius)

{
    assert(radius > 0.0);
}

double Circle::getArea() const
{
    return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
    return {center_, 2*radius_, 2*radius_};
}

void Circle::move(const double moveX, const double moveY)
{
    center_.x+=moveX;
    center_.y+=moveY;
}

void Circle::move(const point_t & new_center)
{
    center_=new_сenter;
}
void Circle::printInf() const
{
    std::cout<<"Center of the circle is "<< center_.x<<","<< center_.y<<"\n";
    std::cout<<"Radius of the circle is "<< radius_<<"\n";
    std::cout<<"Area of the circle is "<<getArea()<<"\n";
    std::cout<<"Parameters of the frame rectangle: "<<"\n";
    std::cout<<"Width: "<<getFrameRect().width <<"\n";
    std::cout<<"Height: "<<getFrameRect().height <<"\n";
    std::cout<<"Coordinates of center: ("<<getFrameRect().pos.x <<","<<getFrameRect().pos.y<<")\n";
}

