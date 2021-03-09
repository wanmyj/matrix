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
    SparseMatrix(const SparseMatrix<T> &rhs) = default; //copy constructor
    SparseMatrix(SparseMatrix<T> &&rhs) = default;      //move constructor
    virtual ~SparseMatrix() = default;

    // Multiplication operator overloading
    DenseMatrix<T>& operator*(const SparseMatrix<T> &rhs);
    template <typename F>
    DenseMatrix<double>& operator*(const SparseMatrix<F> &rhs);
    // Assignment operator overloading
    SparseMatrix<T>& operator=(const SparseMatrix<T> &rhs) = default;
    SparseMatrix<T>& operator=(SparseMatrix<T> &&rhs) = default;

    SparseMatrix<T>& Transpose() noexcept;
    std::shared_ptr<std::vector<std::vector<T>>> GetMatrix() const;
    T GetElemet(const unsigned &, const unsigned &) const;
private:
    template <typename E, typename F>
    E MultiplyHelper(unsigned i, unsigned j, const SparseMatrix<F> &rhs);
};

// Type Diff Scalar/SparseMatrix operations
template <typename T, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
SparseMatrix<double> operator*(const F &lhs, const SparseMatrix<T> &rhs);

// Type Same SparseMatrix/Scalar operations
template <typename T>
SparseMatrix<T> operator*(const SparseMatrix<T> &lhs, const T &rhs);


} // Matrix

#include "Sparse_Matrix.cpp"

#endif
