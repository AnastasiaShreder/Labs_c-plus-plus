#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "circle.hpp"

const double PRECISION = 0.001;

BOOST_AUTO_TEST_SUITE(testCircle)

BOOST_AUTO_TEST_CASE (TestCorrectnessOfCircleRadius)
{
  BOOST_CHECK_THROW(shreder::Circle({{1.0, 6.6}, 0.0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE (TestCorrectnessOfCircleScaleValue)
{
  shreder::Circle testCircle({{5.2, 5.4}, 7.9});
  BOOST_CHECK_THROW(testCircle.scale(-4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestCircleMovingToThePoint)
{
  shreder::Circle testCircle({{7.0, 8.0}, 12.3});
  const double circleAreaBeforeMoving = testCircle.getArea();
  const shreder::rectangle_t frameCircleBeforeMoving = testCircle.getFrameRect();
  testCircle.move({4.0, -1.5});

  BOOST_CHECK_CLOSE(circleAreaBeforeMoving, testCircle.getArea(), PRECISION);
  shreder::rectangle_t frameCircleAfterMoving = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(frameCircleBeforeMoving.height, frameCircleAfterMoving.height, PRECISION);
  BOOST_CHECK_CLOSE(frameCircleBeforeMoving.width, frameCircleAfterMoving.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestCircleMovingAlongAbscissaAndOrdinate)
{
  shreder::Circle testCircle({{6.0, 5.0}, 12.0});
  const double circleAreaBeforeMoving = testCircle.getArea();
  const shreder::rectangle_t frameCircleBeforeMoving = testCircle.getFrameRect();
  testCircle.move({2.5, -7.5});

  BOOST_CHECK_CLOSE(circleAreaBeforeMoving, testCircle.getArea(), PRECISION);
  shreder::rectangle_t frameCircleAfterMoving = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(frameCircleBeforeMoving.height, frameCircleAfterMoving.height, PRECISION);
  BOOST_CHECK_CLOSE(frameCircleBeforeMoving.width, frameCircleAfterMoving.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestCircleAfterScale)
{
  shreder::Circle testCircle({{5.5,3.8},7.9});
  const double circleAreaBeforeZooming = testCircle.getArea();
  const shreder::rectangle_t frameRectangleBeforeZooming = testCircle.getFrameRect();
  const double testScale = 4.0;
  testCircle.scale(testScale);

  BOOST_CHECK_CLOSE(circleAreaBeforeZooming * testScale * testScale, testCircle.getArea(), PRECISION);
  shreder::rectangle_t frameRectangleAfterZooming = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.height * testScale, frameRectangleAfterZooming.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.width * testScale, frameRectangleAfterZooming.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(testCircleAfterRotation)
{
  shreder::Circle testCircle({{8.0, 9.0}, 12.0});
  const double circleAreaBeforeRotation = testCircle.getArea();
  const shreder::rectangle_t frameRectangleBeforeRotation = testCircle.getFrameRect();
  testCircle.rotate(60);

  BOOST_CHECK_CLOSE(circleAreaBeforeRotation, testCircle.getArea(), PRECISION);
  shreder::rectangle_t frameRectAfterRotation = testCircle.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.height, frameRectAfterRotation.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.width, frameRectAfterRotation.width, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.pos.x, frameRectAfterRotation.pos.x, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeRotation.pos.y, frameRectAfterRotation.pos.y, PRECISION);
}

BOOST_AUTO_TEST_SUITE_END()
