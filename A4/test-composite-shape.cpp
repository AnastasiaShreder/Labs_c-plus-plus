#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const double PRECISION = 0.001;

BOOST_AUTO_TEST_SUITE(TestCompositeShape)

BOOST_AUTO_TEST_CASE(TestCompositeShapeAreaAddShape)
{
  shreder::Rectangle testRectangle({{6.0, 5.0}, 12.3, 3.1});
  shreder::Circle testCircle({{6.0, 5.0}, 12.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  const double compositeShapeAreaBeforeAddShape = testCompositeShape.getArea();
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));

  BOOST_CHECK_CLOSE(testCompositeShape.getArea(), testCircle.getArea() + compositeShapeAreaBeforeAddShape, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestCompositeShapeAreaDeleteShape)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 14.3, 3.1});
  shreder::Circle testCircle({{9.0, 4.0}, 1.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const double compositeShapeAreaBeforeDeleteShape = testCompositeShape.getArea();
  testCompositeShape.remove(1);

  BOOST_CHECK_CLOSE(testCompositeShape.getArea(), compositeShapeAreaBeforeDeleteShape - testCircle.getArea(), PRECISION);
}

BOOST_AUTO_TEST_CASE(TestCorrectnessOfDeletingCompositeShape)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 10.0, 10.0});
  shreder::Circle testCircle({{9.0, 4.0}, 1.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));

  BOOST_CHECK_THROW(testCompositeShape.remove(12), std::out_of_range);
  BOOST_CHECK_THROW(testCompositeShape.remove(-7), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(TestAddressWithIncorrectIndex)
{
  shreder::Rectangle testRectangle({{120.0, 8.0}, 11.4, 12.9});
  shreder::Circle testCircle({{1.0, 1.0}, 50.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));

  BOOST_CHECK_THROW(testCompositeShape[4], std::out_of_range);
  BOOST_CHECK_THROW(testCompositeShape[-7], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(TestCompositeShapeMovingToThePoint)
{
  shreder::Rectangle testRectangle({{6.0, 5.0}, 12.3, 3.1});
  shreder::Circle testCircle({{7.0, 8.0}, 12.3});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const double compositeShapeAreaBeforeMoving = testCompositeShape.getArea();
  const shreder::rectangle_t frameRectangleBeforeMoving = testCompositeShape.getFrameRect();
  testCompositeShape.move({1.5, 3.6});

  BOOST_CHECK_CLOSE(testCompositeShape.getArea(), compositeShapeAreaBeforeMoving, PRECISION);
  shreder::rectangle_t frameRectangleAfterMoving = testCompositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.height, frameRectangleAfterMoving.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeMoving.width, frameRectangleAfterMoving.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestCompositeShapeMovingAlongAbscissaAndOrdinate)
{
  shreder::Rectangle testRectangle({{6.0, 5.0}, 12.3, 3.1});
  shreder::Circle testCircle({{6.0, 5.0}, 12.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const double compositeShapeAreaBeforeMoving = testCompositeShape.getArea();
  const shreder::rectangle_t frameRectangleBeforeMoving = testCompositeShape.getFrameRect();
  testCompositeShape.move(2.0, -1.8);

  BOOST_CHECK_CLOSE(testCompositeShape.getArea(), compositeShapeAreaBeforeMoving, PRECISION);
  shreder::rectangle_t frameRectangleAfterMoving = testCompositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleAfterMoving.width, frameRectangleBeforeMoving.width, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleAfterMoving.height, frameRectangleBeforeMoving.height, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestCompositeShapeScale)
{
  shreder::Rectangle testRectangle({{6.0, 5.0}, 12.3, 3.1});;
  shreder::Circle testCircle({{5.5,3.8},7.9});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const double compositeShapeAreaBeforeZooming = testCompositeShape.getArea();
  const shreder::rectangle_t frameRectangleBeforeZooming = testCompositeShape.getFrameRect();
  const double testScale = 3.0;
  testCompositeShape.scale(testScale);

  BOOST_CHECK_CLOSE(testCompositeShape.getArea(), compositeShapeAreaBeforeZooming * testScale * testScale, PRECISION);
  shreder::rectangle_t frameRectangleAfterZooming = testCompositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.height * testScale, frameRectangleAfterZooming.height, PRECISION);
  BOOST_CHECK_CLOSE(frameRectangleBeforeZooming.width * testScale, frameRectangleAfterZooming.width, PRECISION);
}

BOOST_AUTO_TEST_CASE(TestCorrectnessOfScaleValueCompositeShape)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 14.3, 3.1});
  shreder::Circle testCircle({{9.0, 4.0}, 1.0});
  shreder::Circle testCircle1({{6.0, 5.0}, 12.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle1));

  BOOST_CHECK_THROW(testCompositeShape.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(TestMoveEmptyCompositeShape)
{
  shreder::CompositeShape testCompositeShape;

  BOOST_CHECK_THROW(testCompositeShape.move(5.0, 5.0), std::logic_error);
  BOOST_CHECK_THROW(testCompositeShape.move({-1.0, -1.0}), std::logic_error);
}

BOOST_AUTO_TEST_CASE(TestGetParametersEmptyCompositeShape)
{
  shreder::CompositeShape testCompositeShape;

  BOOST_CHECK_THROW(testCompositeShape.getArea(), std::logic_error);
  BOOST_CHECK_THROW(testCompositeShape.getFrameRect(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(testCompositeShapeCopyConstructor)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 10.5, 6.9});
  shreder::Circle testCircle({{8.0, 9.0}, 12.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const shreder::rectangle_t frameRectangle = testCompositeShape.getFrameRect();
  shreder::CompositeShape copyCompositeShape(testCompositeShape);

  BOOST_CHECK_CLOSE(copyCompositeShape.getArea(), testCompositeShape.getArea(), PRECISION);
  BOOST_CHECK_EQUAL(copyCompositeShape.getCount(), testCompositeShape.getCount());
  shreder::rectangle_t copyFrameRectangle = copyCompositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(copyFrameRectangle.width, frameRectangle.width, PRECISION);
  BOOST_CHECK_CLOSE(copyFrameRectangle.height, frameRectangle.height, PRECISION);
  BOOST_CHECK_CLOSE(copyFrameRectangle.pos.x, frameRectangle.pos.x, PRECISION);
  BOOST_CHECK_CLOSE(copyFrameRectangle.pos.y, frameRectangle.pos.y, PRECISION);
}

BOOST_AUTO_TEST_CASE(testCompositeShapeMoveConstructor)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 10.5, 6.9});
  shreder::Circle testCircle({{8.0, 9.0}, 12.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const shreder::rectangle_t frameRectangle = testCompositeShape.getFrameRect();
  const double compositeShapeArea = testCompositeShape.getArea();
  const std::size_t countOfShapes = testCompositeShape.getCount();
  shreder::CompositeShape moveCompositeShape(std::move(testCompositeShape));

  BOOST_CHECK_CLOSE(moveCompositeShape.getArea(), compositeShapeArea, PRECISION);
  shreder::rectangle_t moveFrameRectangle = moveCompositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(moveFrameRectangle.width, frameRectangle.width, PRECISION);
  BOOST_CHECK_CLOSE(moveFrameRectangle.height, frameRectangle.height, PRECISION);
  BOOST_CHECK_CLOSE(moveFrameRectangle.pos.x, frameRectangle.pos.x, PRECISION);
  BOOST_CHECK_CLOSE(moveFrameRectangle.pos.y, frameRectangle.pos.y, PRECISION);
  BOOST_CHECK_EQUAL(moveCompositeShape.getCount(), countOfShapes);

  BOOST_CHECK_EQUAL(0, testCompositeShape.getCount());
}

BOOST_AUTO_TEST_CASE(testCompositeShapeCopyOperator)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 10.5, 6.9});
  shreder::Circle testCircle({{8.0, 9.0}, 12.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const shreder::rectangle_t frameRectangle = testCompositeShape.getFrameRect();
  shreder::CompositeShape newCompositeShape = testCompositeShape;

  BOOST_CHECK_CLOSE(newCompositeShape.getArea(), testCompositeShape.getArea(), PRECISION);
  BOOST_CHECK_EQUAL(newCompositeShape.getCount(), testCompositeShape.getCount());
  shreder::rectangle_t copyFrameRectangle = newCompositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(copyFrameRectangle.width, frameRectangle.width,PRECISION);
  BOOST_CHECK_CLOSE(copyFrameRectangle.height, frameRectangle.height, PRECISION);
  BOOST_CHECK_CLOSE(copyFrameRectangle.pos.x, frameRectangle.pos.x, PRECISION);
  BOOST_CHECK_CLOSE(copyFrameRectangle.pos.y, frameRectangle.pos.y, PRECISION);
}

BOOST_AUTO_TEST_CASE(testCompositeShapeMoveOperator)
{
  shreder::Rectangle testRectangle({{8.0, 9.0}, 10.5, 6.9});
  shreder::Circle testCircle({{8.0, 9.0}, 12.0});
  shreder::CompositeShape testCompositeShape(std::make_shared<shreder::Rectangle>(testRectangle));
  testCompositeShape.add(std::make_shared<shreder::Circle>(testCircle));
  const shreder::rectangle_t frameRectangle = testCompositeShape.getFrameRect();
  const double compositeShapeArea = testCompositeShape.getArea();
  const std::size_t countOfShapes = testCompositeShape.getCount();
  shreder::CompositeShape moveCompositeShape = std::move(testCompositeShape);

  BOOST_CHECK_CLOSE(moveCompositeShape.getArea(), compositeShapeArea, PRECISION);
  shreder::rectangle_t moveFrameRectangle = moveCompositeShape.getFrameRect();
  BOOST_CHECK_CLOSE(moveFrameRectangle.width, frameRectangle.width, PRECISION);
  BOOST_CHECK_CLOSE(moveFrameRectangle.height, frameRectangle.height, PRECISION);
  BOOST_CHECK_CLOSE(moveFrameRectangle.pos.x, frameRectangle.pos.x, PRECISION);
  BOOST_CHECK_CLOSE(moveFrameRectangle.pos.y, frameRectangle.pos.y, PRECISION);
  BOOST_CHECK_EQUAL(moveCompositeShape.getCount(), countOfShapes);

  BOOST_CHECK_EQUAL(0, testCompositeShape.getCount());
}

BOOST_AUTO_TEST_SUITE_END()
