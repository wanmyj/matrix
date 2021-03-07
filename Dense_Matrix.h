#ifndef __DENSE_MATRIX_H
#define __DENSE_MATRIX_H

#include "Base_Matrix.h"

namespace Matrix {

template <typename T>
class DenseMatrix : public BaseMatrix<T>
{
private:
    std::vector<std::vector<T>> m_mat;
public:
    DenseMatrix();
    DenseMatrix(std::initializer_list<std::initializer_list<T>> init);
    DenseMatrix(const ProductExpr<T> &rhs); //copy constructor
    DenseMatrix(const DenseMatrix<T> &rhs); //copy constructor
    DenseMatrix(DenseMatrix<T> &&rhs) = default;      //move contrructor
    virtual ~DenseMatrix() = default;

    // Assignment operator overloading
    DenseMatrix<T>& operator=(const ProductExpr<T> &rhs);
    DenseMatrix<T>& operator=(const BaseMatrix<T> &rhs);
    DenseMatrix<T>& operator=(const DenseMatrix<T> &rhs);
    DenseMatrix<T>& operator=(DenseMatrix<T> &&rhs) = default;

    DenseMatrix<T>& Transpose();
    std::shared_ptr<std::vector<std::vector<T>>> GetMatrix() const;
private:
    inline void UnityMatrix(unsigned, unsigned, const T &);
    inline void CopyFromMat(const std::vector<std::vector<T>>&);
};

} // Matrix

#include "Dense_Matrix.cpp"

#endif