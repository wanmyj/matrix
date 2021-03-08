#ifndef __SPARSE_MATRIX_CPP
#define __SPARSE_MATRIX_CPP

#include "Sparse_Matrix.h"

namespace Matrix
{

template <typename T>
SparseMatrix<T>::SparseMatrix()
{
    m_mat[0].resize(1, 1);
    m_mat[1].resize(1, 1);
    m_mat[2].resize(1, 0);
}

// Parameter Constructor
template <typename T>
SparseMatrix<T>::SparseMatrix
    (std::initializer_list<std::initializer_list<T>> init)
{
    unsigned elementNums = init.size() - 1;
    if (*(init.begin()).size() != 2) {
        throw std::invalid_argument
            ( "the first curly brace should be the number of rows and cols");
    }
    for
    for (auto& it : init) {
        cols = cols > it.size() ? cols : it.size();
    }
    UnityMatrix(rows, cols, 0);
    unsigned i = 0;
    unsigned j = 0;
    for (auto& aRow : init) {
        for (auto& element : aRow) {
            m_mat[i][j] = element;
            j++;
        }
        j = 0;
        i++;
    }
    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = rows;
}

template <typename T>
template <typename F>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<F> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    std::vector<std::vector<F>> aVec= *(rhs.GetMatrix());
    BaseMatrix<T>::m_rows = aVec.size();
    BaseMatrix<T>::m_cols = aVec[0].size();
    m_mat.resize(BaseMatrix<T>::m_rows);
    for (unsigned i = 0; i < m_mat.size(); i++) {
        m_mat[i].resize(BaseMatrix<T>::m_cols);
    }

    for (unsigned i = 0; i < BaseMatrix<T>::m_rows; i++) {
        for (unsigned j = 0; j < BaseMatrix<T>::m_cols; j++) {
            m_mat[i][j] = aVec[i][j];
        }
    }
}

template <typename T>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    CopyFromMat(*rhs.GetMatrix());
}

// Multiplication operator overloading
template <typename T>
DenseMatrix<T>& SparseMatrix<T>::operator*(const SparseMatrix<T> &rhs)
{
    if (this->get_rows() != rhs.get_rows()) {
        throw std::invalid_argument( "two diag matrices are NOT multipliable");
    }

    std::vector<T> res(this->get_rows());
    for (unsigned i = 0; i < m_mat.size(); i++) {
        res[i] = GetElement(i) * rhs.GetElement(i);
    }
    return DenseMatrix<T>(res);
}

template <typename T>
template <typename F>
DenseMatrix<double>& SparseMatrix<T>::operator*(const SparseMatrix<F> &rhs)
{
    if (this->get_rows() != rhs.get_rows()) {
        throw std::invalid_argument( "two diag matrices are NOT multipliable");
    }

    std::vector<double> res(this->get_rows());
    for (unsigned i = 0; i < m_mat.size(); i++) {
        res[i] = GetElement(i) * rhs.GetElement(i);
    }
    return DenseMatrix<double>(res);
}

// Assignment Operator
template <typename T>
SparseMatrix<T> &SparseMatrix<T>::operator=(const SparseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    CopyFromMat(*rhs.GetMatrix());
    return *this;
}

// BaseType Assignment Operator
template <typename T>
SparseMatrix<T> &SparseMatrix<T>::operator=(const BaseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);

    CopyFromMat(*(rhs.GetMatrix()));
    return *this;
}

// BaseType Assignment Operator
template <typename T>
SparseMatrix<T> &SparseMatrix<T>::operator=(const ProductExpr<T> &rhs)
{
    CopyFromMat(rhs.m_mat);
    return *this;
}

template <typename T>
void SparseMatrix<T>::CopyFromMat(const std::vector<std::vector<T>> &aVec)
{
    // when called, please make sure only v<v<T>> of mat form passed
    BaseMatrix<T>::m_rows = aVec.size();
    BaseMatrix<T>::m_cols = aVec[0].size();
    m_mat.resize(BaseMatrix<T>::m_rows);
    for (unsigned i = 0; i < m_mat.size(); i++) {
        m_mat[i].resize(BaseMatrix<T>::m_cols);
    }

    for (unsigned i = 0; i < BaseMatrix<T>::m_rows; i++) {
        for (unsigned j = 0; j < BaseMatrix<T>::m_cols; j++) {
            m_mat[i][j] = aVec[i][j];
        }
    }
}


// Calculate a transpose of this matrix
template <typename T>
SparseMatrix<T>& SparseMatrix<T>::Transpose()
{
    std::vector<std::vector<T>> resMat;
    resMat.resize(BaseMatrix<T>::m_cols);
    for (unsigned i = 0; i < resMat.size(); i++) {
        resMat[i].resize(BaseMatrix<T>::m_rows);
    }

    for (unsigned i = 0; i < BaseMatrix<T>::m_rows; i++) {
        for (unsigned j = 0; j < BaseMatrix<T>::m_cols; j++) {
            resMat[j][i] = m_mat[i][j];
        }
    }

    m_mat = resMat;
    BaseMatrix<T>::m_cols = BaseMatrix<T>::m_rows;
    BaseMatrix<T>::m_rows = m_mat.size();
    return *this;
}

template <typename T>
std::shared_ptr<std::vector<std::vector<T>>> SparseMatrix<T>::GetMatrix() const
{
    std::shared_ptr<std::vector<std::vector<T>>>
        res(new std::vector<std::vector<T>>(m_mat));
    return res;
}

// // Access the individual elements
// template <typename T>
// std::vector<T> &SparseMatrix<T>::operator[](const unsigned &row)
// {
//     return this->(*m_ptr);
// }

template <typename T>
void SparseMatrix<T>::UnityMatrix(unsigned rows, unsigned cols, const T &init)
{
    m_mat.resize(rows);
    for (unsigned i = 0; i < m_mat.size(); i++) {
        m_mat[i].resize(cols, init);
    }
    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = cols;
}

} // Matrix

#endif