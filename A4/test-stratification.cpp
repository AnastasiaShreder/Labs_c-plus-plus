#include <stdexcept>
#include <boost/test/auto_unit_test.hpp>
#include "stratification.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

BOOST_AUTO_TEST_SUITE(testStratification)

BOOST_AUTO_TEST_CASE(testStratificationCorrectWorking)
{
  shreder::Rectangle rect({{0, 0}, 5, 6});
  shreder::Rectangle rect1({{0, -4}, 1, 4});
  shreder::Circle circl({{20, 20}, 3});
  shreder::CompositeShape compShape(std::make_shared<shreder::Rectangle>(rect));
  compShape.add(std::make_shared<shreder::Rectangle>(rect1));
  compShape.add(std::make_shared<shreder::Circle>(circl));

  shreder::Matrix<shreder::Shape> matrix = shreder::layer(compShape);
  BOOST_CHECK_EQUAL(matrix.getRows(), 2);
  BOOST_CHECK_EQUAL(matrix[0].getCount(), 2);
  BOOST_CHECK_EQUAL(matrix[1].getCount(), 1);
  BOOST_CHECK_EQUAL(matrix[0][0], compShape[0]);
  BOOST_CHECK_EQUAL(matrix[0][1], compShape[2]);
  BOOST_CHECK_EQUAL(matrix[1][0], compShape[1]);
}

BOOST_AUTO_TEST_CASE(testCrossing)
{
  shreder::Rectangle rect1({{0, 0}, 5, 6});
  shreder::Rectangle rect2({{0, -4}, 1, 4});
  shreder::Circle circle1({{5, 0}, 1});
  shreder::Rectangle rect3({{0, 4}, 1, 4});
  shreder::Circle circle2({{-3, 0}, 2});
  shreder::Triangle tri({{6.0, 5.0}, {12.0, 10.9}, {15.6, 7.9}});

  BOOST_CHECK(shreder::cross(rect1, rect2));
  BOOST_CHECK(shreder::cross(rect1, circle2));
  BOOST_CHECK(shreder::cross(rect1, rect3));
  BOOST_CHECK(shreder::cross(rect1, circle2));

  BOOST_CHECK(!shreder::cross(rect1, circle1));
}

BOOST_AUTO_TEST_CASE(testEmptyStratification)
{
  shreder::CompositeShape compShape;
  shreder::Matrix<shreder::Shape> matrix = shreder::layer(compShape);

  BOOST_CHECK_EQUAL(matrix.getRows(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
