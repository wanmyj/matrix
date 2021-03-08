#ifndef __DIAG_MATRIX_CPP
#define __DIAG_MATRIX_CPP

#include "Diag_Matrix.h"

namespace Matrix
{

template <typename T>
DiagMatrix<T>::DiagMatrix()
: m_mat(1, 0) {}

template <typename T>
DiagMatrix<T>::DiagMatrix(std::vector<T> init)
:   BaseMatrix<T>::m_rows(init.size()),
    BaseMatrix<T>::m_cols(init.size()),
    m_mat(init)
{}

// Parameter Constructor
template <typename T>
DiagMatrix<T>::DiagMatrix(std::initializer_list<T> init)
{
    unsigned rows = init.size();
    m_mat.resize(rows);

    for (size_t i = 0; i < rows; i++)
    {
        m_mat[i] = *(init.begin() + i);
    }

    BaseMatrix<T>::m_rows = rows;
    BaseMatrix<T>::m_cols = rows;
}

template <typename T>
template <typename F>
DiagMatrix<T>::DiagMatrix(const DiagMatrix<F> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    m_mat.resize(rhs.get_rows());
    for (unsigned i = 0; i < m_mat.size(); i++) {
        m_mat[i] = rhs.GetElement(i);
    }
}

//copy constructor
template <typename T>
DiagMatrix<T>::DiagMatrix(const DiagMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    m_mat.resize(rhs.get_rows());
    for (unsigned i = 0; i < m_mat.size(); i++) {
        m_mat[i] = rhs.GetElement(i);
    }
}

// Multiplication operator overloading
template <typename T>
DiagMatrix<T>& DiagMatrix<T>::operator*(const DiagMatrix<T> &rhs)
{
    if (this->get_rows() != rhs.get_rows()) {
        throw std::invalid_argument( "two diag matrices are NOT multipliable");
    }

    std::vector<T> res(this->get_rows());
    for (unsigned i = 0; i < m_mat.size(); i++) {
        res[i] = GetElement(i) * rhs.GetElement(i);
    }
    return DiagMatrix<T>(res);
}

template <typename T>
template <typename F>
DiagMatrix<double>& DiagMatrix<T>::operator*(const DiagMatrix<F> &rhs)
{
    if (this->get_rows() != rhs.get_rows()) {
        throw std::invalid_argument( "two diag matrices are NOT multipliable");
    }

    std::vector<double> res(this->get_rows());
    for (unsigned i = 0; i < m_mat.size(); i++) {
        res[i] = GetElement(i) * rhs.GetElement(i);
    }
    return DiagMatrix<double>(res);
}
// Assignment Operator
template <typename T>
DiagMatrix<T>& DiagMatrix<T>::operator=(const DiagMatrix<T> &rhs)
{
    BaseMatrix<T>::operator=(rhs);
    m_mat.resize(rhs.get_rows());
    for (unsigned i = 0; i < m_mat.size(); i++) {
        m_mat[i] = rhs.GetElement(i);
    }
    return *this;
}

template <typename T>
std::shared_ptr<std::vector<std::vector<T>>> DiagMatrix<T>::GetMatrix() const
{
    unsigned i = this->get_cols();
    std::shared_ptr<std::vector<std::vector<T>>>
        res(new std::vector<std::vector<T>>(i, std::vector<T>(i, 0)));
    for (size_t j = 0; j < i; j++) {
        res[j][j] = GetElement(j);
    }
    
    return res;
}

template <typename T>
T DiagMatrix<T>::GetElement(const unsigned &order) const
{
    return m_mat.at(order);
}

} // Matrix

#endif