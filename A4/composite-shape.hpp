#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace shreder
{
  class CompositeShape : public Shape
  {
    public:
      CompositeShape();
      CompositeShape(const CompositeShape &);
      CompositeShape(CompositeShape &&) noexcept;
      CompositeShape(const shape_ptr &);
      ~CompositeShape() = default;



      CompositeShape & operator =(const CompositeShape &);
      CompositeShape & operator =(CompositeShape &&) noexcept;
      shape_ptr operator [](std::size_t) const;

      double getArea() const override;
      rectangle_t getFrameRect() const override;
      std::size_t getCount() const;
      void move(double, double) override;
      void move(const point_t &) override;
      void scale(double) override;
      void rotate(double) override;
      void add(const shape_ptr &);
      void remove(std::size_t);
      double sine(double) const;
      double cosine(double) const;
      void printInf() const override;

    private:
      std::size_t count_;
      array_ptr arrOfShapes_;
  };
}

#endif
