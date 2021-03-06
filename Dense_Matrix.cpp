#ifndef __BASE_MATRIX_CPP
#define __BASE_MATRIX_CPP

#include "Dense_Matrix.h"

namespace Matrix
{

template <typename T>
DenseMatrix<T>::DenseMatrix()
{
    m_ptr = std::make_shared<std::vector<std::vector<T>>>(m_mat);
}

// Parameter Constructor
template <typename T>
DenseMatrix<T>::DenseMatrix
    (std::initializer_list<std::initializer_list<T>> init)
{
    unsigned rows = init.size();
    unsigned cols = 0;
    for (auto& it : init) {
        cols = cols > it.size() ? cols : it.size();
    }
    UnityMatrix(rows, cols, 0);
    unsigned i = 0;
    unsigned j = 0;
    for (auto& aRow : init) {
        for (auto& element : aRow) {
            m_mat[i][j] = it;
            j++;
        }
        j = 0
        i++;
    }
}

// Assignment Operator
template <typename T>
DenseMatrix<T> &DenseMatrix<T>::operator=(const DenseMatrix<T> &rhs)
{
    return *this;
}


// Calculate a transpose of this matrix
template <typename T>
DenseMatrix<T> DenseMatrix<T>::transpose()
{
    DenseMatrix result(m_rows, m_cols, 0.0);

    for (unsigned i = 0; i < m_rows; i++)
    {
        for (unsigned j = 0; j < m_cols; j++)
        {
            result(i, j) = this->m_mat[j][i];
        }
    }

    return result;
}

// Multiply a matrix with a vector
template <typename T>
std::vector<T> DenseMatrix<T>::operator*(const std::vector<T> &rhs)
{
    std::vector<T> result(rhs.size(), 0.0);

    for (unsigned i = 0; i < m_rows; i++)
    {
        for (unsigned j = 0; j < m_cols; j++)
        {
            result[i] = this->m_mat[i][j] * rhs[j];
        }
    }

    return result;
}


template <typename T>
std::shared_ptr<std::vector<std::vector<T>>> DenseMatrix<T>::GetMatrix()
{
    return m_ptr;
}

// Access the individual elements
template <typename T>
std::vector<T> &DenseMatrix<T>::operator[](const unsigned &row)
{
    return this->m_mat;
}

template <typename T>
void DenseMatrix<T>::UnityMatrix(unsigned rows, unsigned cols, const T &init)
{
    m_mat.resize(rows);
    for (unsigned i = 0; i < m_mat.size(); i++)
    {
        m_mat[i].resize(cols, _initial);
    }
    m_rows = rows;
    m_cols = cols;
    for (unsigned i = 0; i < lrow; i++) {
        for (unsigned j = 0; j < rcol; j++) {
            m_mat[i][j] = init;
        }
    }
}

} // Matrix

#endif