//#include <boost/test/auto_unit_test.hpp>
#define BOOST_TEST_MODULE A4
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "triangle.hpp"

const double PRECISION = 0.001;

BOOST_AUTO_TEST_SUITE(testTriangle)

BOOST_AUTO_TEST_CASE(TestCorrectnessOfTriangleParameters)
{
  BOOST_CHECK_THROW(shreder::Triangle testTriangle({0.5, 0.5}, {0.5, 0.5}, {3.0, 4.0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestCorrectnessOfTriangleScaleValue)
{
  shreder::Triangle testTriangle({0.0, 0.0}, {1.0, 4.0}, {5.0, 7.0});
  BOOST_CHECK_THROW(testTriangle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestTriangleMovingToThePoint)
{
  shreder::Triangle testTriangle({{6.0, 5.0}, {12.3, 3.1}, {5.0, 9.3}});
  const double triangleAreaBeforeMoving = testTriangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeMoving = testTriangle.getFrameRect();
  testTriangle.move({4.0, -1.5});

  BOOST_CHECK_CLOSE(triangleAreaBeforeMoving, testTriangle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterMoving = testTriangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.height, frameRectangleAfterMoving.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.width, frameRectangleAfterMoving.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestTriangleMovingAlongAbscissaAndOrdinate)
{
  shreder::Triangle testTriangle({{6.0, 5.0}, {12.0, 10.9}, {15.6, 7.9}});
  const double triangleAreaBeforeMoving = testTriangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeMoving = testTriangle.getFrameRect();
  testTriangle.move({2.5, -7.5});

  BOOST_CHECK_CLOSE(triangleAreaBeforeMoving, testTriangle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterMoving = testTriangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.height, frameRectangleAfterMoving.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.width, frameRectangleAfterMoving.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestTriangleAfterScale)
{
  shreder::Triangle testTriangle({{5.5,3.8}, {7.9, 8.3}, {0.0, 0.0}});
  const double triangleAreaBeforeZooming = testTriangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeZooming = testTriangle.getFrameRect();
  const double testScale = 4.0;
  testTriangle.scale(testScale);


  BOOST_CHECK_CLOSE(triangleAreaBeforeZooming * testScale * testScale, testTriangle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterZooming = testTriangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.height * testScale, frameRectangleAfterZooming.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.width * testScale, frameRectangleAfterZooming.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(testTriangleRotate)
{
  shreder::Triangle testTriangle({0.0, 0.0}, {7.1, 5.3}, {11.0, 5.0});
  double triangleAreaBeforeRotating = testTriangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeRotating = testTriangle.getFrameRect();

  double angle = 90.0;
  testTriangle.rotate(angle);
  BOOST_CHECK_CLOSE(triangleAreaBeforeRotating, testTriangle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterRotating = testTriangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotating.height, frameRectangleAfterRotating.width, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotating.width, frameRectangleAfterRotating.height, PRECISION);

}

BOOST_AUTO_TEST_SUITE_END();
