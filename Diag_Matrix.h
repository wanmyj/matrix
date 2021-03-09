#ifndef __DIAG_MATRIX_H
#define __DIAG_MATRIX_H

#include "Base_Matrix.h"

namespace Matrix {

template <typename T>
class DiagMatrix : public BaseMatrix<T>
{
private:
    std::vector<T> m_mat;
public:
    DiagMatrix();
    DiagMatrix(std::vector<T>);
    DiagMatrix(std::initializer_list<T> init);
    template <typename F>
    DiagMatrix(const DiagMatrix<F> &rhs);
    DiagMatrix(const DiagMatrix<T> &rhs);           //copy constructor
    DiagMatrix(DiagMatrix<T> &&rhs) noexcept = default;      //move constructor
    virtual ~DiagMatrix() = default;

    // Multiplication operator overloading
    DiagMatrix<T> operator*(const DiagMatrix<T> &rhs);
    template <typename F>
    DiagMatrix<double> operator*(const DiagMatrix<F> &rhs);
    // Assignment operator overloading
    DiagMatrix<T>& operator=(const DiagMatrix<T> &rhs);
    DiagMatrix<T>& operator=(DiagMatrix<T> &&rhs) = default;

    DiagMatrix<T>& Transpose() {};
    std::shared_ptr<std::vector<std::vector<T>>> GetMatrix() const;
    T GetElement(const unsigned &) const;
private:
};

// Type Diff Scalar/DiagMatrix operations
template <typename T, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
DiagMatrix<double> operator*(const F &lhs, const DiagMatrix<T> &rhs);

// Type Same DiagMatrix/Scalar operations
template <typename T>
DiagMatrix<T> operator*(const DiagMatrix<T> &lhs, const T &rhs);

} // Matrix

#include "Diag_Matrix.cpp"

#endif