#ifndef __SPARSE_MATRIX_CPP
#define __SPARSE_MATRIX_CPP

#include "Sparse_Matrix.h"
#include <set>

namespace Matrix
{

template <typename T>
SparseMatrix<T>::SparseMatrix()
{
    m_mat[0].resize(1, 0);
    m_mat[1].resize(1, 0);
    m_mat[2].resize(1, 0);
}

// Parameter Constructor
template <typename T>
SparseMatrix<T>::SparseMatrix(unsigned rows, unsigned cols,
    std::vector<std::vector<T>> init)
{
    if (init.size() != 3) {
        throw std::invalid_argument( "the vector<vector> size should be 3");
    }
    if (init[0].size() != init[1].size() || init[1].size != init[2].size()) {
        throw std::invalid_argument( "the 3 vector size should be equal");
    }

    unsigned elementNums = init[0].size();
    for (size_t i = 0; i < elementNums; i++) {
        if (init[0][i] > rows || init[1][i] > cols) {
            throw std::invalid_argument( "the coord is ourside of matrix");
        }
    }

    m_mat = init;
    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = rows;
    m_elementNums = elementNums;
}

// Parameter Constructor
template <typename T>
SparseMatrix<T>::SparseMatrix(unsigned rows, unsigned cols,
    std::initializer_list<std::initializer_list<T>> init)
{
    unsigned elementNums = init.size();
    for (auto& it : init) {
        if (it.size() != 3) {
            throw std::invalid_argument( "the list size should be 3");
        }
        if (*(it.begin()) > rows || *(it.begin() + 1) > cols) {
            throw std::invalid_argument( "the coord is ourside of matrix");
        }
    }

    m_mat[0].resize(elementNums);
    m_mat[1].resize(elementNums);
    m_mat[2].resize(elementNums);
    unsigned i = 0;
    for (auto& it : init) {
        if (*(it.begin() + 2) == 0) {
            elementNums--;
            continue;
        }
        m_mat[0][i] = *(it.begin() + 0);
        m_mat[1][i] = *(it.begin() + 1);
        m_mat[2][i] = *(it.begin() + 2);
        i++;
    }

    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = rows;
    m_elementNums = elementNums;
}

template <typename T>
template <typename F>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<F> &rhs)
{
    BaseMatrix<T>::m_rows = rhs.get_rows();
    BaseMatrix<T>::m_cols = rhs.get_cols();

    unsigned i = 0;
    unsigned j = 0;
    for (auto aRow : rhs.m_mat) {
        for (auto element : aRow) {
            m_mat[i][j] = element;
            j++;
        }
        j = 0;
        i++;
    }
}

// Multiplication operator overloading
template <typename T>
DenseMatrix<T>& SparseMatrix<T>::operator*(const SparseMatrix<T> &rhs)
{
    if (this->get_cols() != rhs.get_rows()) {
        throw std::invalid_argument( "two diag matrices are NOT multipliable");
    }
    std::set<unsigned> rowLhsSet;
    std::set<unsigned> colRhsSet;
    for (auto& it : m_rowVec) {
        rowLhsSet.insert(it);
    }
    for (auto& it : rhs.m_colVec) {
        colRhsSet.insert(it);
    }

    std::vector<unsigned> colLhsVec;
    std::vector<unsigned> rowRhsVec;
    std::vector<std::vector<T>> res(m_rows, std::vector<T>(rhs.m_cols, 0));
    for (auto& i : rowLhsSet) {
        for (auto& j : colRhsSet) {
            res[i][j] = MultiplyHelper<T, T>(i, j, rhs);
        }
    }
    return {res};
}

template <typename T>
template <typename E, typename F>
E SparseMatrix<T>::MultiplyHelper(unsigned i, unsigned j,
    const SparseMatrix<F> &rhs)
{
    E res {0};
    for (unsigned k = 0; k < m_cols; k++) {
        auto func = [](unsigned x) {return x == k;};
        auto itBegin = m_colVec.begin();
        auto iter = itBegin;
        auto itEnd = m_colVec.end();
        E left {0};
        while ((iter = std::find_if(iter, itEnd, func)) != itEnd) {
            unsigned dis = iter - itBegin;
            if (m_rowVec[dis] == i) {
                left = m_valueVec[dis];
                break;
            }
        }
        if (left == 0) continue;

        itBegin = rhs.m_rowVec.begin();
        iter = itBegin;
        itEnd = rhs.m_rowVec.end();
        E right {0};
        while ((iter = std::find_if(iter, itEnd, func)) != itEnd) {
            unsigned dis = iter - itBegin;
            if (m_colVec[dis] == j) {
                right = rhs.m_valueVec[dis];
                break;
            }
        }
        if (right == 0) continue;

        if (m_colVec.find(k) == m_colVec.end() ||
            rhs.m_rowVec.find(k) == rhs.m_rowVec.end()) {
            continue;
        }
        res += left * right;
    }
    return res;

}


template <typename T>
template <typename F>
DenseMatrix<double>& SparseMatrix<T>::operator*(const SparseMatrix<F> &rhs)
{
    if (this->get_cols() != rhs.get_rows()) {
        throw std::invalid_argument( "two diag matrices are NOT multipliable");
    }
    std::set<unsigned> rowLhsSet;
    std::set<unsigned> colRhsSet;
    for (auto& it : m_rowVec) {
        rowLhsSet.insert(it);
    }
    for (auto& it : rhs.m_colVec) {
        colRhsSet.insert(it);
    }

    std::vector<unsigned> colLhsVec;
    std::vector<unsigned> rowRhsVec;
    std::vector<std::vector<double>> 
        res(m_rows, std::vector<double>(rhs.m_cols, 0));
    for (auto& i : rowLhsSet) {
        for (auto& j : colRhsSet) {
            res[i][j] = MultiplyHelper<double, F>(i, j, rhs);
        }
    }
    return {res};
}

// Calculate a transpose of this matrix
template <typename T>
SparseMatrix<T>& SparseMatrix<T>::Transpose()
{
    std::vector<unsigned> mid;
    mid = std::move(m_rowVec);
    m_rowVec = std::move(m_colVec);
    m_colVec = std::move(mid);

    return *this;
}

template <typename T>
std::shared_ptr<std::vector<std::vector<T>>> SparseMatrix<T>::GetMatrix() const
{
    std::shared_ptr<std::vector<std::vector<T>>>
        res(new std::vector<m_rows, std::vector<T>>(m_cols, 0));
    for (int i = 0; i < m_elementNums; i++) {
        (*res)[m_rowVec[i]][m_colVec[i]] = m_valueVec[i];
    }
    return res;
}

} // Matrix

#endif