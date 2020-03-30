#include <iostream>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "matrix.hpp"
#include "stratification.hpp"

int main()
{
  shreder::Rectangle rect({{7, 5}, 1, 3});
  shreder::Circle circl({{11, 8}, 20});
  shreder::Triangle tri({{6.0, 5.0}, {12.3, 3.1}, {5.0, 9.3}});

  std::cout << "Creating of composite shape...\n";
  shreder::CompositeShape compShape(std::make_shared<shreder::Rectangle>(rect));
  compShape.add(std::make_shared<shreder::Circle> (circl));
  compShape.add(std::make_shared<shreder::Triangle> (tri));
  std::cout << "Description of composite shape: \n";
  compShape.printInf();
  std::cout << "\n";
  std::cout << "Moving to the point with coordinates (35, 7)\n";
  compShape.move({35, 7});
  compShape.printInf();
  std::cout << "\n";
  std::cout << "Moving along abscissa for 4 and along ordinate for 6\n";
  compShape.move(4, 6);
  compShape.printInf();
  std::cout << "\n";
  std::cout << "Zoom scale of composite shape in two times and get new parameters\n";
  compShape.scale(2);
  compShape.printInf();
  std::cout << "\n";
  std::cout << "Rotating composite shape by 90 degrees\n";
  compShape.rotate(90);
  compShape.printInf();
  std::cout << "\n";
  std::cout << "Deleting shape under number 2 \n";
  compShape.remove(2);
  compShape.printInf();
  std::cout << "\n";
  std::cout << "Description of shape under number 1\n";
  std::shared_ptr<shreder::Shape> selectedShape = compShape[0];
  selectedShape->printInf();
  std::cout << "\n";

  compShape.add(std::make_shared<shreder::Circle> (circl));
  compShape.add(std::make_shared<shreder::Triangle> (tri));

  std::cout << "Matrix:";
  std::cout << "\n";

  shreder::Matrix<shreder::Shape> matrix = shreder::layer(compShape);

  for (std::size_t i = 0; i < matrix.getRows(); ++i)
  {
    std::cout << "Actual layer " << i + 1 << '\n';
    std::cout << "Shapes on this layer:\n";
    for (std::size_t j = 0; j < matrix[i].getCount(); ++j)
    {
      std::cout << j + 1 << '\n';
      std::cout << "Area of the shape " << matrix[i][j]->getArea() << '\n';
      const shreder::point_t centerShape = matrix[i][j]->getFrameRect().pos;
      std::cout << "Center of the shape (" << centerShape.x << "," << centerShape.y << ")\n";
    }
  }

  std::cout << "\n";
  std::cout << "Ready!\n";
  std::cout << "\n";

  return 0;
}
