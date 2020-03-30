#include "stratification.hpp"
#include <cmath>

shreder::Matrix<shreder::Shape> shreder::layer(const shreder::CompositeShape & compShape)
{
  shreder::Matrix<shreder::Shape> matrix;
  for (std::size_t i = 0; i < compShape.getCount(); ++i)
  {
    std::size_t row = 0;
    std::size_t j = matrix.getRows();
    while (j-- > 0)
    {
      for (std::size_t k = 0; k < matrix[j].getCount(); ++k)
      {
        if (cross(* compShape[i], *matrix[j][k]))
        {
          row = j + 1;
          break;
        }
      }
      if (row)
      {
        break;
      }
    }
    matrix.add(row, compShape[i]);
  }
  return matrix;
}

bool shreder::cross(const shreder::Shape & Shape1, const shreder::Shape & Shape2)
{
  const shreder::rectangle_t FrameRect1 = Shape1.getFrameRect();
  const shreder::rectangle_t FrameRect2 = Shape2.getFrameRect();
  if (std::abs(FrameRect1.pos.x - FrameRect2.pos.x) > (FrameRect1.width + FrameRect2.width) / 2)
  {
    return false;
  }
  if (std::abs(FrameRect1.pos.y - FrameRect2.pos.y) > (FrameRect1.height + FrameRect2.height) / 2)
  {
    return false;
  }
  return true;
}

