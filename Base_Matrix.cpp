#ifndef __BASE_MATRIX_CPP
#define __BASE_MATRIX_CPP

#include "Base_Matrix.h"

namespace Matrix {

// Copy Constructor
template <typename T>
BaseMatrix<T>::BaseMatrix(const BaseMatrix<T> &rhs)
{
    m_rows = rhs.get_rows();
    m_cols = rhs.get_cols();
}

// (Virtual) Destructor
template <typename T>
BaseMatrix<T>::~BaseMatrix() {}

// Assignment Operator
template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(const BaseMatrix<T> &rhs)
{
    m_rows = rhs.get_rows();
    m_cols = rhs.get_cols();
    return *this;
}

// rvalue Assignment Operator
template <typename T>
BaseMatrix<T>& BaseMatrix<T>::operator=(BaseMatrix<T> &&rhs)
{
    m_rows = rhs.get_rows();
    m_cols = rhs.get_cols();
    return *this;
}

// // Access the individual elements
// template <typename T>
// std::vector<T> &BaseMatrix<T>::operator[](const unsigned &row)
// {
//     std::shared_ptr<std::vector<std::vector<T>>> mat = GetMatrix();
//     return mat->[row];
// }

// // Access the individual elements (const)
// template <typename T>
// const std::vector<T> &BaseMatrix<T>::operator[](const unsigned &row) const
// {
//     std::shared_ptr<std::vector<std::vector<T>>> mat = GetMatrix();
//     return mat->[row];
// }

// Get the number of m_rows of the matrix
template <typename T>
unsigned BaseMatrix<T>::get_rows() const
{
    return this->m_rows;
}

// Get the number of columns of the matrix
template <typename T>
unsigned BaseMatrix<T>::get_cols() const
{
    return this->m_cols;
}

} // Matrix
#endif