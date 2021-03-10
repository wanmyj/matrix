#ifndef __SPARSE_MATRIX_CPP
#define __SPARSE_MATRIX_CPP

#include "Sparse_Matrix.h"
#include <set>
#include <algorithm>

namespace Matrix
{

template <typename T>
SparseMatrix<T>::SparseMatrix()
{
    m_rowVec.resize(1, 0);
    m_colVec.resize(1, 0);
    m_valueVec.resize(1, 0);
    m_elementNums = 1;
}

// Parameter Constructor
template <typename T>
SparseMatrix<T>::SparseMatrix(unsigned rows, unsigned cols,
    std::vector<unsigned> rVec, std::vector<unsigned> cVec, std::vector<T> init)
{
    if (rVec.size() != cVec.size() || cVec.size() != init.size()) {
        throw std::invalid_argument("the 3 vector size should be equal");
    }

    unsigned elementNums = init.size();
    for (size_t i = 0; i < elementNums; i++) {
        if (rVec[i] > rows || cVec[i] > cols) {
            throw std::invalid_argument("the coord is ourside of matrix");
        }
    }

    m_rowVec = rVec;
    m_colVec = cVec;
    m_valueVec = init;
    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = cols;
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
            throw std::invalid_argument("the list size should be 3");
        }
        if (*(it.begin()) > rows || *(it.begin() + 1) > cols) {
            throw std::invalid_argument("the coord is ourside of matrix");
        }
    }

    m_rowVec.resize(elementNums);
    m_colVec.resize(elementNums);
    m_valueVec.resize(elementNums);
    unsigned i = 0;
    for (auto& it : init) {
        if (*(it.begin() + 2) == 0) {
            elementNums--;
            continue;
        }
        m_rowVec[i] = *(it.begin() + 0);
        m_colVec[i] = *(it.begin() + 1);
        m_valueVec[i] = *(it.begin() + 2);
        i++;
    }

    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = cols;
    m_elementNums = elementNums;
}

template <typename T>
template <typename F>
SparseMatrix<T>::SparseMatrix(const SparseMatrix<F> &rhs)
{
    BaseMatrix<T>::m_rows = rhs.get_rows();
    BaseMatrix<T>::m_cols = rhs.get_cols();
    m_elementNums = rhs.m_elementNums;

    unsigned i = 0;
    unsigned j = 0;
    m_rowVec = rhs.m_rowVec;
    m_colVec = rhs.m_colVec;
    m_valueVec.resize(rhs.m_elementNums);
    for (size_t i = 0; i < m_elementNums; i++) {
        m_valueVec[i] = rhs.m_valueVec[i];
    }
}

// Multiplication operator overloading
template <typename T>
DenseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix<T> &rhs)
{
    if (this->get_cols() != rhs.get_rows()) {
        throw std::invalid_argument("two diag matrices are NOT multipliable");
    }
    std::set<unsigned> rowLhsSet;
    std::set<unsigned> colRhsSet;
    for (auto& it : m_rowVec) {
        rowLhsSet.insert(it);
    }
    for (auto& it : rhs.m_colVec) {
        colRhsSet.insert(it);
    }
    unsigned rows = this->get_rows();
    unsigned cols = rhs.get_cols();
    std::vector<unsigned> colLhsVec;
    std::vector<unsigned> rowRhsVec;
    std::vector<std::vector<T>> res(rows, std::vector<T>(cols, 0));
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
    for (unsigned k = 0; k < this->get_cols(); k++) {
        auto func = [=](unsigned x) {return x == k;};
        auto itBegin = m_colVec.begin();
        auto iter = itBegin;
        auto itEnd = m_colVec.end();
        E left {0};
        while ((iter = std::find_if(iter, itEnd, func)) != itEnd) {
            iter++;
            unsigned dis = iter - itBegin;
            if (m_rowVec[dis] == i) {
                left = m_valueVec[dis];
                break;
            }
        }
        if (left == 0) continue;

        auto rhsRowVec = rhs.GetRowsVec();
        itBegin = rhsRowVec.begin();
        iter = itBegin;
        itEnd = rhsRowVec.end();
        E right {0};
        while ((iter = std::find_if(iter, itEnd, func)) != itEnd) {
            iter++;
            unsigned dis = iter - itBegin;
            if (m_colVec[dis] == j) {
                right = rhs.GetValsVec()[dis];
                break;
            }
        }
        if (right == 0) continue;

        res += left * right;
    }
    return res;
}


template <typename T>
template <typename F>
DenseMatrix<double> SparseMatrix<T>::operator*(const SparseMatrix<F> &rhs)
{
    if (this->get_cols() != rhs.get_rows()) {
        throw std::invalid_argument("two diag matrices are NOT multipliable");
    }
    std::set<unsigned> rowLhsSet;
    std::set<unsigned> colRhsSet;
    for (auto& it : m_rowVec) {
        rowLhsSet.insert(it);
    }
    auto colVec = rhs.GetColsVec();
    for (auto& it : colVec) {
        colRhsSet.insert(it);
    }

    unsigned rows = this->get_rows();
    unsigned cols = rhs.get_cols();
    std::vector<unsigned> colLhsVec;
    std::vector<unsigned> rowRhsVec;
    std::vector<std::vector<double>>
        res(rows, std::vector<double>(cols, 0));
    for (auto& i : rowLhsSet) {
        for (auto& j : colRhsSet) {
            res[i][j] = MultiplyHelper<double, F>(i, j, rhs);
        }
    }
    return {res};
}

template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator*(const T &rhs)
{
    std::vector<T> val(m_elementNums, 0);
    for (size_t i = 0; i < m_elementNums; i++) {
        val[i] = m_valueVec[i] * rhs;
    }
    return {this->get_rows(), this->get_cols(), m_rowVec, m_colVec, val};
}

template <typename T>
template <typename F>
SparseMatrix<double> SparseMatrix<T>::operator*(const F &rhs)
{
    std::vector<double> val(m_elementNums, 0);
    for (size_t i = 0; i < m_elementNums; i++) {
        val[i] = m_valueVec[i] * rhs;
    }
    return {this->get_rows(), this->get_cols(), m_rowVec, m_colVec, val};
}

// Calculate a transpose of this matrix
template <typename T>
SparseMatrix<T>& SparseMatrix<T>::Transpose() noexcept
{
    std::vector<unsigned> mid;
    mid = std::move(m_rowVec);
    m_rowVec = std::move(m_colVec);
    m_colVec = std::move(mid);
    unsigned midv = BaseMatrix<T>::m_rows;
    BaseMatrix<T>::m_rows = BaseMatrix<T>::m_cols;
    BaseMatrix<T>::m_cols = midv;
    return *this;
}

template <typename T>
std::shared_ptr<std::vector<std::vector<T>>> SparseMatrix<T>::GetMatrix() const
{
    unsigned rows = this->get_rows();
    unsigned cols = this->get_cols();
    std::shared_ptr<std::vector<std::vector<T>>>
        res(new std::vector<std::vector<T>>(rows,std::vector<T>(cols, 0)));
    for (int i = 0; i < m_elementNums; i++) {
        (*res)[m_rowVec[i]][m_colVec[i]] = m_valueVec[i];
    }
    return res;
}

template <typename T>
std::vector<unsigned> SparseMatrix<T>::GetRowsVec() const
{
    return this->m_rowVec;
}

template <typename T>
std::vector<unsigned> SparseMatrix<T>::GetColsVec() const
{
    return this->m_colVec;
}

template <typename T>
std::vector<T> SparseMatrix<T>::GetValsVec() const
{
    return this->m_valueVec;
}

// Type Diff Scalar/SparseMatrix operations
template <typename E, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
SparseMatrix<double> operator*(const F &lhs, const SparseMatrix<E> &rhs)
{
    std::vector<unsigned> rows = rhs.GetRowsVec();
    std::vector<unsigned> cols = rhs.GetColsVec();
    std::vector<E> vals = rhs.GetValsVec();
    std::vector<double> valNew(cols.size(), 0);
    for (size_t i = 0; i < cols.size(); i++) {
        valNew[i] = vals[i] * lhs;
    }
    return {rhs.get_rows(), rhs.get_cols(), rows, cols, valNew};
}

} // Matrix

#endif