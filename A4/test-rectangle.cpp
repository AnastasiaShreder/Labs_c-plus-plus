#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "rectangle.hpp"

const double PRECISION = 0.001;

BOOST_AUTO_TEST_SUITE(testRectangle)

BOOST_AUTO_TEST_CASE (TestCorrectnessOfRectangleParameters)
{
  BOOST_CHECK_THROW(shreder::Rectangle({{5.6, 4.0}, -3.5, -1.7}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE (TestCorrectnessOfRectangleScaleValue)
{
  shreder::Rectangle testRectangle({{1.0,5.0},5.1,4.2});
  BOOST_CHECK_THROW(testRectangle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestRectangleMovingToThePoint)
{
  shreder::Rectangle testRectangle({{6.0, 5.0}, 12.3, 3.1});
  const double rectangleAreaBeforeMoving = testRectangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeMoving = testRectangle.getFrameRect();
  testRectangle.move({4.0, -1.5});

  BOOST_CHECK_CLOSE(rectangleAreaBeforeMoving, testRectangle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterMoving = testRectangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.height, frameRectangleAfterMoving.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.width, frameRectangleAfterMoving.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestRectangleMovingAlongAbscissaAndOrdinate)
{
  shreder::Rectangle testRectangle({{6.0, 5.0}, 12.3, 3.1});
  const double rectangleAreaBeforeMoving = testRectangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeMoving = testRectangle.getFrameRect();
  testRectangle.move({2.0, -0.5});

  BOOST_CHECK_CLOSE(rectangleAreaBeforeMoving, testRectangle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterMoving = testRectangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.height, frameRectangleAfterMoving.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.width, frameRectangleAfterMoving.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestRectangleAfterScale)
{
  shreder::Rectangle testRectangle({{6.0, 5.0}, 12.3, 3.1});
  const double rectangleAreaBeforeZooming = testRectangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeZooming = testRectangle.getFrameRect();
  const double testScale = 4.0;
  testRectangle.scale(testScale);

  BOOST_CHECK_CLOSE(rectangleAreaBeforeZooming * testScale * testScale, testRectangle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterZooming = testRectangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.height * testScale, frameRectangleAfterZooming.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.width * testScale, frameRectangleAfterZooming.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(testRectangleAfterRotation)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 10.5, 6.9});
  const double rectangleAreaBeforeRotation = testRectangle.getArea();
  const shreder::rectangle_t frameRectangleBeforeRotation = testRectangle.getFrameRect();
  testRectangle.rotate(90);


  BOOST_CHECK_CLOSE(testRectangle.getArea(), rectangleAreaBeforeRotation, PRECISION);
  shreder::rectangle_t frameRectAfterRotation = testRectangle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.height, frameRectAfterRotation.width, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.width, frameRectAfterRotation.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.pos.x, frameRectAfterRotation.pos.x, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.pos.y, frameRectAfterRotation.pos.y, PRECISION);
}

BOOST_AUTO_TEST_SUITE_END()
