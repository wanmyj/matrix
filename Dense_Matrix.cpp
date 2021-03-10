#ifndef __DASE_MATRIX_CPP
#define __DASE_MATRIX_CPP

#include "Dense_Matrix.h"

namespace Matrix
{

template <typename T>
DenseMatrix<T>::DenseMatrix()
{
    UnityMatrix(BaseMatrix<T>::m_rows, BaseMatrix<T>::m_cols, 0);
}

template <typename T>
DenseMatrix<T>::DenseMatrix(std::vector<std::vector<T>> init)
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
            m_mat[i][j] = element;
            j++;
        }
        j = 0;
        i++;
    }
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
            m_mat[i][j] = element;
            j++;
        }
        j = 0;
        i++;
    }
}

template <typename T>
template <typename F>
DenseMatrix<T>::DenseMatrix(const DenseMatrix<F> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    std::vector<std::vector<F>> aVec = *(rhs.GetMatrix());
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
template <typename F>
DenseMatrix<T>::DenseMatrix(const ProductExpr<F> &rhs)
{
    std::vector<std::vector<F>> aVec = rhs.m_mat;
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
DenseMatrix<T>::DenseMatrix(const DenseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    CopyFromMat(*rhs.GetMatrix());
}

template <typename T>
DenseMatrix<T>::DenseMatrix(const ProductExpr<T> &rhs)
{
    CopyFromMat(rhs.m_mat);
}

// Assignment Operator
template <typename T>
DenseMatrix<T> &DenseMatrix<T>::operator=(const DenseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    CopyFromMat(*rhs.GetMatrix());
    return *this;
}

// BaseType Assignment Operator
template <typename T>
DenseMatrix<T> &DenseMatrix<T>::operator=(const BaseMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);

    CopyFromMat(*(rhs.GetMatrix()));
    return *this;
}

// ProductType Assignment Operator
template <typename T>
DenseMatrix<T> &DenseMatrix<T>::operator=(const ProductExpr<T> &rhs)
{
    CopyFromMat(rhs.m_mat);
    return *this;
}

template <typename T>
void DenseMatrix<T>::CopyFromMat(const std::vector<std::vector<T>> &aVec)
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
DenseMatrix<T>& DenseMatrix<T>::Transpose()
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
std::shared_ptr<std::vector<std::vector<T>>> DenseMatrix<T>::GetMatrix() const
{
    std::shared_ptr<std::vector<std::vector<T>>>
        res(new std::vector<std::vector<T>>(m_mat));
    return res;
}

template <typename T>
void DenseMatrix<T>::UnityMatrix(unsigned rows, unsigned cols, const T &init)
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