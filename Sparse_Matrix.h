#ifndef __SPARSE_MATRIX_H
#define __SPARSE_MATRIX_H

#include "Base_Matrix.h"
#include "Dense_Matrix.h"

namespace Matrix {

template <typename T>
class SparseMatrix : public BaseMatrix<T>
{
private:
    std::vector<unsigned> m_rowVec;
    std::vector<unsigned> m_colVec;
    std::vector<T> m_valueVec;
    unsigned m_elementNums;
public:
    SparseMatrix();
    SparseMatrix(unsigned, unsigned,
        std::vector<unsigned>, std::vector<unsigned>, std::vector<T>);
    SparseMatrix(unsigned rows, unsigned cols,
        std::initializer_list<std::initializer_list<T>> init);
    template <typename F>
    SparseMatrix(const SparseMatrix<F> &rhs);
    SparseMatrix(const SparseMatrix<T> &rhs) = default; // copy constructor
    SparseMatrix(SparseMatrix<T> &&rhs) = default;      // move constructor
    virtual ~SparseMatrix() = default;

    // Multiplication operator overloading
    DenseMatrix<T> operator*(const SparseMatrix<T> &rhs);
    template <typename F>
    DenseMatrix<double> operator*(const SparseMatrix<F> &rhs);

    // Type Same Scalar/SparseMatrix operations
    SparseMatrix<T> operator*(const T &rhs);
    // Type Diff Scalar/SparseMatrix operations
    template <typename F,
        typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
    SparseMatrix<double> operator*(const F &rhs)
    {
        std::vector<double> val(m_elementNums, 0);
        for (size_t i = 0; i < m_elementNums; i++) {
            val[i] = m_valueVec[i] * rhs;
        }
        return {this->get_rows(), this->get_cols(), m_rowVec, m_colVec, val};
    }
    // Assignment operator overloading
    SparseMatrix<T>& operator=(const SparseMatrix<T> &rhs) = default;
    SparseMatrix<T>& operator=(SparseMatrix<T> &&rhs) = default;

    SparseMatrix<T>& Transpose() noexcept;
    std::shared_ptr<std::vector<std::vector<T>>> GetMatrix() const;
    std::vector<unsigned> GetRowsVec() const;
    std::vector<unsigned> GetColsVec() const;
    std::vector<T> GetValsVec() const;
private:
    template <typename E, typename F>
    E MultiplyHelper(unsigned i, unsigned j, const SparseMatrix<F> &rhs);

// Type Same SparseMatrix/Scalar operations
    friend SparseMatrix operator*(const T &lhs, const SparseMatrix &rhs)
    {
        std::vector<T> val(rhs.m_elementNums, 0);
        for (size_t i = 0; i < rhs.m_elementNums; i++) {
            val[i] = rhs.m_valueVec[i] * lhs;
        }

        unsigned row = rhs.get_rows();
        unsigned col = rhs.get_cols();
        return {row, col, rhs.m_rowVec, rhs.m_colVec, val};
    }
};

// Type Diff Scalar/SparseMatrix operations
template <typename E, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
SparseMatrix<double> operator*(const F &lhs, const SparseMatrix<E> &rhs);

} // Matrix

#include "Sparse_Matrix.cpp"

#endif
