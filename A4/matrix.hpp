#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include <stdexcept>

namespace shreder
{
template <typename T>
class Matrix
{
public:
  using ptrType = std::shared_ptr<T>;
  using arrType = std::unique_ptr<ptrType []>;

  class Layer
  {
  public:
    Layer(const Layer &);
    Layer(Layer &&) noexcept;
    Layer(ptrType *, std::size_t);
    ~Layer() = default;

    Layer &operator =(const Layer &);
    Layer &operator =(Layer &&) noexcept;
    ptrType operator [](std::size_t) const;

    std::size_t getCount() const;

  private:
    std::size_t count_;
    arrType data_;
  };

  Matrix();
  Matrix(const Matrix &);
  Matrix(Matrix &&) noexcept;
  ~Matrix() = default;

  Matrix & operator =(const Matrix &);
  Matrix & operator =(Matrix &&) noexcept;

  Layer operator [](std::size_t) const;
  bool operator ==(const Matrix &) const;
  bool operator !=(const Matrix &) const;

  std::size_t getRows() const;
  void swap(Matrix &) noexcept;
  void add(std::size_t, ptrType);

private:
  std::size_t rows_;
  std::size_t count_;
  std::unique_ptr<std::size_t []> layerSize_;
  arrType data_;
};
template <typename T>
Matrix<T>::Matrix():
        rows_(0),
        count_(0)
{
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> & copyMatrix):
        rows_(copyMatrix.rows_),
        count_(copyMatrix.count_),
        layerSize_(std::make_unique<std::size_t []>(copyMatrix.rows_)),
        data_(std::make_unique<ptrType []>(copyMatrix.count_))
{
  for (std::size_t i = 0; i < rows_; ++i)
  {
    layerSize_[i] = copyMatrix.layerSize_[i];
  }

  for (std::size_t i = 0; i < count_; ++i)
  {
    data_[i] = copyMatrix.data_[i];
  }
}
template <typename T>
Matrix<T>::Matrix(Matrix<T> && moveMatrix) noexcept :
        rows_(moveMatrix.rows_),
        count_(moveMatrix.count_),
        layerSize_(std::move(moveMatrix.layerSize_)),
        data_(std::move(moveMatrix.data_))
{
  moveMatrix.rows_ = 0;
  moveMatrix.count_ = 0;
}
template <typename T>
Matrix<T> & Matrix<T>::operator =(const Matrix<T> & copyMatrix)
{
  if (this != & copyMatrix)
  {
    swap(Matrix<T>(copyMatrix));
  }
  return *this;
}
template <typename T>
Matrix<T> & Matrix<T>::operator =(Matrix<T> && moveMatrix) noexcept
{
  if (this != & moveMatrix)
  {
    rows_ = moveMatrix.rows_;
    moveMatrix.rows_ = 0;
    count_ = moveMatrix.count_;
    moveMatrix.count_ = 0;
    layerSize_ = std::move(moveMatrix.layerSize_);
    data_ = std::move(moveMatrix.data_);
  }
  return *this;
}

template <typename T>
typename Matrix<T>::Layer Matrix<T>::operator [](std::size_t row) const
{
  if (row >= rows_)
  {
    throw std::out_of_range("Incorrect row number");
  }
  std::size_t rowNumber= 0;
  for (std::size_t i = 0; i < row; ++i)
  {
    rowNumber += layerSize_[i];
  }
  return Layer(& data_[rowNumber], layerSize_[row]);
}
template <typename T>
bool Matrix<T>::operator ==(const Matrix<T> & rhs) const
{
  if ((rows_ != rhs.rows_) || (count_ != rhs.count_))
  {
    return false;
  }
  for (std::size_t i = 0; i < rows_; ++i)
  {
    if (layerSize_[i] != rhs.layerSize_[i])
    {
      return false;
    }
  }
  for (std::size_t i = 0; i < count_; ++i)
  {
    if (data_[i] != rhs.data_[i])
    {
      return false;
    }
  }
  return true;
}
template <typename T>
bool Matrix<T>::operator !=(const Matrix<T> & rhs) const
{
  return !(*this == rhs);
}
template <typename T>
std::size_t Matrix<T>::getRows() const
{
  return rows_;
}
template <typename T>
void Matrix<T>::swap(Matrix<T> & swapMatrix) noexcept
{
  std::swap(rows_, swapMatrix.rows_);
  std::swap(count_, swapMatrix.counter_);
  std::swap(layerSize_, swapMatrix.layerSize_);
  std::swap(data_, swapMatrix.data_);
}
template <typename T>
void Matrix<T>::add(std::size_t row, ptrType object)
{
  if (row > rows_)
  {
    throw std::out_of_range("Incorrect row number");
  }
  if (object == nullptr)
  {
    throw std::invalid_argument("You cannot add nullptr");
  }
  if (row == rows_)
  {
    std::unique_ptr<std::size_t []> tempLayerSize = std::make_unique<std::size_t []>(rows_ + 1);
    arrType tempData = std::make_unique<ptrType []>(count_ + 1);
    for (std::size_t i = 0; i < rows_; ++i)
    {
      tempLayerSize[i] = layerSize_[i];
    }
    tempLayerSize[rows_++] = 1;
    layerSize_ = std::move(tempLayerSize);
    for (std::size_t i = 0; i < count_; ++i)
    {
      tempData[i] = data_[i];
    }
    tempData[count_++] = object;
    data_ = std::move(tempData);
  }
  else
  {
    arrType tempData = std::make_unique<ptrType []>(count_ + 1);
    std::size_t newIndex = 0;
    std::size_t oldIndex = 0;
    for (std::size_t i = 0; i < rows_; ++i)
    {
      for (std::size_t k = 0; k < layerSize_[i]; ++k)
      {
        tempData[newIndex++] = data_[oldIndex++];
      }
      if (i == row)
      {
        tempData[newIndex++] = object;
      }
    }
    data_ = std::move(tempData);
    ++layerSize_[row];
    ++count_;
  }
}
template <typename T>
Matrix<T>::Layer::Layer(const Matrix<T>::Layer & copyLayer) :
        count_(copyLayer.count_),
        data_(std::make_unique<ptrType []>(copyLayer.count_))
{
  for (std::size_t i = 0; i < count_; ++i)
  {
    data_[i] = copyLayer.data_[i];
  }
}
template <typename T>
Matrix<T>::Layer::Layer(Matrix<T>::Layer && moveLayer) noexcept :
        count_(moveLayer.count_),
        data_(std::move(moveLayer.data_))
{
  moveLayer.count_= 0;
}
template <typename T>
Matrix<T>::Layer::Layer(Matrix<T>::ptrType * array, std::size_t size) :
        count_(size),
        data_(std::make_unique<ptrType []>(size))
{
  for (std::size_t i = 0; i < count_; ++i)
  {
    data_[i] = array[i];
  }
}
template <typename T>
typename Matrix<T>::Layer & Matrix<T>::Layer::operator =(const Matrix<T>::Layer & copyLayer)
{
  if (this != & copyLayer)
  {
    data_ = std::make_unique<ptrType  []>(copyLayer.count_);
    for (std::size_t i = 0; i < copyLayer.count_; ++i)
    {
      data_[i] = copyLayer.data_[i];
    }
    count_ = copyLayer.count_;
  }
  return *this;
}
template <typename T>
typename Matrix<T>::Layer & Matrix<T>::Layer::operator =(Matrix<T>::Layer && moveLayer) noexcept
{
  if (this != & moveLayer)
  {
    count_ = moveLayer.count_;
    moveLayer.count_ = 0;
    data_ = std::move(moveLayer.data_);
  }
  return *this;
}
template <typename T>
typename Matrix<T>::ptrType Matrix<T>::Layer::operator [](std::size_t number) const
{
  if (number >= count_)
  {
    throw std::out_of_range("Incorrect number of shape in layer");
  }
  return data_[number];
}
template <typename T>
std::size_t Matrix<T>::Layer::getCount() const
{
  return count_;
}
}

#endif
