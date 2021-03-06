#ifndef __DENSE_MATRIX_H
#define __DENSE_MATRIX_H

#include "Base_Matrix.h"

namespace Matrix {

template <typename T>
class DenseMatrix : public BaseMatrix
{
private:
    std::vector<std::vector<T>> m_mat;
    std::shared_ptr<std::vector<std::vector<T>>> m_ptr;
public:
    DenseMatrix();
    DenseMatrix(std::initializer_list<std::initializer_list<T>> init);
    DenseMatrix(const DenseMatrix<T> &rhs); //copy contrructor
    DenseMatrix(DenseMatrix<T> &&rhs) = default;      //move contrructor
    virtual ~DenseMatrix() = default;

    // Assignment operator overloading
    DenseMatrix<T> &operator=(const ProduceExpt<T> &rhs);
    DenseMatrix<T> &operator=(const BaseMatrix<T> &rhs);
    DenseMatrix<T> &operator=(const DenseMatrix<T> &rhs);
    DenseMatrix<T> &operator=(DenseMatrix<T> &&rhs) = default;

    DenseMatrix<T> Transpose();
    std::shared_ptr<std::vector<std::vector<T>>> GetMatrix();
private:
    void UnityMatrix(unsigned , unsigned , const T &);
};

} // Matrix

#include "Base_Matrix.cpp"

#endif