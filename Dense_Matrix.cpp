#ifndef __DASE_MATRIX_CPP
#define __DASE_MATRIX_CPP

#include "Dense_Matrix.h"

namespace Matrix
{

template <typename T>
DenseMatrix<T>::DenseMatrix()
{
    m_ptr = std::make_shared<std::vector<std::vector<T>>>();
    UnityMatrix(BaseMatrix<T>::m_rows, BaseMatrix<T>::m_cols, 0);
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
            (*m_ptr)[i][j] = element;
            j++;
        }
        j = 0;
        i++;
    }
}

// Assignment Operator
template <typename T>
DenseMatrix<T> &DenseMatrix<T>::operator=(const DenseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    m_ptr = std::make_shared<std::vector<std::vector<T>>>();

    CopyFromMat(*rhs.GetMatrix());
    return *this;
}

// BaseType Assignment Operator
template <typename T>
DenseMatrix<T> &DenseMatrix<T>::operator=(const BaseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    m_ptr = std::make_shared<std::vector<std::vector<T>>>();

    CopyFromMat(*(rhs.GetMatrix()));
    return *this;
}

// BaseType Assignment Operator
template <typename T>
DenseMatrix<T> &DenseMatrix<T>::operator=(const ProductExpr<T> &rhs)
{
    m_ptr = std::make_shared<std::vector<std::vector<T>>>();

    CopyFromMat(rhs.m_mat);
    return *this;
}

template <typename T>
void DenseMatrix<T>::CopyFromMat(const std::vector<std::vector<T>> &aVec)
{
    // when called, please make sure only v<v<T>> of mat form passed
    BaseMatrix<T>::m_rows = aVec.size();
    BaseMatrix<T>::m_cols = aVec[0].size();
    (*m_ptr).resize(BaseMatrix<T>::m_rows);
    for (unsigned i = 0; i < (*m_ptr).size(); i++) {
        (*m_ptr)[i].resize(BaseMatrix<T>::m_cols);
    }

    for (unsigned i = 0; i < BaseMatrix<T>::m_rows; i++) {
        for (unsigned j = 0; j < BaseMatrix<T>::m_cols; j++) {
            (*m_ptr)[i][j] = aVec[i][j];
        }
    }
}


// Calculate a transpose of this matrix
template <typename T>
DenseMatrix<T>& DenseMatrix<T>::Transpose()
{
    std::shared_ptr<std::vector<std::vector<T>>> resMat;
    (*resMat).resize(BaseMatrix<T>::m_cols);
    for (unsigned i = 0; i < (*resMat).size(); i++) {
        (*resMat)[i].resize(BaseMatrix<T>::m_rows);
    }

    for (unsigned i = 0; i < BaseMatrix<T>::m_rows; i++) {
        for (unsigned j = 0; j < BaseMatrix<T>::m_cols; j++) {
            (*resMat)[j][i] = (*m_ptr)[i][j];
        }
    }

    m_ptr = resMat;
    BaseMatrix<T>::m_cols = BaseMatrix<T>::m_rows;
    BaseMatrix<T>::m_rows = (*m_ptr).size();
    return *this;
}

template <typename T>
std::shared_ptr<std::vector<std::vector<T>>> DenseMatrix<T>::GetMatrix() const
{
    return m_ptr;
}

// // Access the individual elements
// template <typename T>
// std::vector<T> &DenseMatrix<T>::operator[](const unsigned &row)
// {
//     return this->(*m_ptr);
// }

template <typename T>
void DenseMatrix<T>::UnityMatrix(unsigned rows, unsigned cols, const T &init)
{
    (*m_ptr).resize(rows);
    for (unsigned i = 0; i < (*m_ptr).size(); i++) {
        (*m_ptr)[i].resize(cols, init);
    }
    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = cols;
}

} // Matrix

#endif