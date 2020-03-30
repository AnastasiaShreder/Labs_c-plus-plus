#include <memory>
#include <stdexcept>
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/auto_unit_test.hpp>
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

BOOST_AUTO_TEST_SUITE(testMatrix)

BOOST_AUTO_TEST_CASE(testMatrixCopyConstructor)
{
  shreder::Matrix<int> testMatrix;
  const std::size_t row = 5;
  const std::size_t column = 5;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < column; ++j)
    {
      testMatrix.add(i, std::make_shared<int> (i + j));
    }
  }
  shreder::Matrix<int> copyMatrix(testMatrix);

  BOOST_CHECK(copyMatrix == testMatrix);
}

BOOST_AUTO_TEST_CASE(testMatrixMoveConstructor)
{
  shreder::Matrix<int> testMatrix;
  const std::size_t row = 5;
  const std::size_t column = 5;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < column; ++j)
    {
      testMatrix.add(i, std::make_shared<int> (i + j));
    }
  }
  shreder::Matrix<int> tempMatrix(testMatrix);
  shreder::Matrix<int> moveMatrix(std::move(testMatrix));

  BOOST_CHECK(moveMatrix == tempMatrix);
}

BOOST_AUTO_TEST_CASE(testMatrixCopyOperator)
{
  shreder::Matrix<int> testMatrix;
  const std::size_t row = 5;
  const std::size_t column = 5;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < column; ++j)
    {
      testMatrix.add(i, std::make_shared<int>(i + j));
    }
  }
  shreder::Matrix<int> copyMatrix = testMatrix;

  BOOST_CHECK(copyMatrix == testMatrix);
}

BOOST_AUTO_TEST_CASE(testMatrixMoveOperator)
{
  shreder::Matrix<int> testMatrix;
  const std::size_t row = 5;
  const std::size_t column = 5;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < column; ++j)
    {
      testMatrix.add(i, std::make_shared<int> (i + j));
    }
  }
  shreder::Matrix<int> tempMatrix(testMatrix);
  shreder::Matrix<int> moveMatrix = std::move(testMatrix);

  BOOST_CHECK(moveMatrix == tempMatrix);
}

BOOST_AUTO_TEST_CASE(testMatrixEqualityOperator)
{
  shreder::Matrix<int> testMatrix;
  const std::size_t row = 5;
  const std::size_t column = 5;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < column; ++j)
    {
      testMatrix.add(i, std::make_shared<int> (i + j));
    }
  }
  shreder::Matrix<int> copyMatrix(testMatrix);
  shreder::Matrix<int> emptyMatrix;

  BOOST_CHECK_EQUAL(copyMatrix == testMatrix, true);
  BOOST_CHECK_EQUAL(emptyMatrix == testMatrix, false);
}

BOOST_AUTO_TEST_CASE(testMatrixInequalityOperator)
{
  shreder::Matrix<int> testMatrix;
  const std::size_t row = 5;
  const std::size_t column = 5;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < column; ++j)
    {
      testMatrix.add(i, std::make_shared<int> (i + j));
    }
  }
  shreder::Matrix<int> copyMatrix(testMatrix);
  shreder::Matrix<int> emptyMatrix;

  BOOST_CHECK_EQUAL(copyMatrix != testMatrix, false);
  BOOST_CHECK_EQUAL(emptyMatrix != testMatrix, true);
}

BOOST_AUTO_TEST_CASE(testMatrixGetMethodByCorrectIndex)
{
  shreder::Matrix<int> testMatrix;
  const std::size_t row = 5;
  const std::size_t column = 5;
  for (std::size_t i = 0; i < row; ++i)
  {
    for (std::size_t j = 0; j < column; ++j)
    {
      testMatrix.add(i, std::make_shared<int> (i + j));
    }
  }

  BOOST_CHECK_THROW(testMatrix[10][10], std::out_of_range);
  BOOST_CHECK_THROW(testMatrix[-10][-10], std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
