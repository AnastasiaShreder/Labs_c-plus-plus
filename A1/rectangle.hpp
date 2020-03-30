#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const point_t& center, const double width, const double height):
        center_(center),
        width_(width),
        height_(height)

{
    assert((width > 0) && (height > 0));
}

double Rectangle::getArea() const
{
    return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const
{
    return {center_, width_, height_};
}

void Rectangle::move(const double moveX, const double moveY)
{
    center_.x+=moveX;
    center_.y+=moveY;
}

void Rectangle::move(const point_t & new_Center)
{
    center_=new_Center;
}

void Rectangle::printInf() const
{
    std::cout<<"Center of the rectangle is "<< center_.x<<","<< center_.y<<"\n";
    std::cout<<"Width of the rectangle is "<< width_<<"\n";
    std::cout<<"Height of the rectangle is "<<height_<<"\n";
    std::cout<<"Area of the rectangle is "<<getArea()<<"\n";
    std::cout<<"Parameters of the frame rectangle: "<<"\n";
    std::cout<<"Width: "<<getFrameRect().width <<"\n";
    std::cout<<"Height: "<<getFrameRect().height <<"\n";
    std::cout<<"Coordinates of center: ("<<getFrameRect().pos.x <<","<<getFrameRect().pos.y<<")\n";
}


