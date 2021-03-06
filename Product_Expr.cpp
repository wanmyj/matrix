#include "Product_Expr.h"

namespace Matrix {

template <typename T>
template <typename F, typename E>
ProductExpr<T>::ProductExpr(const BaseMatrix<E> &lhs, const BaseMatrix<F> &rhs)
{
    std::shared_ptr<std::vector<std::vector<T>>> lmat = lhs.GetMatrix();
    unsigned lrow = lhs.get_rows();
    unsigned lcol = lhs.get_cols();

    std::shared_ptr<std::vector<std::vector<F>>> rmat = rhs.GetMatrix();
    unsigned rrow = rhs.get_rows();
    unsigned rcol = rhs.get_cols();

    m_mat.resize(lrow);
    for (unsigned i = 0; i < lrow; i++) {
        m_mat[i].resize(rcol);
    }

    for (unsigned i = 0; i < lrow; i++) {
        for (unsigned j = 0; j < rcol; j++) {
            m_mat[i][j] = 0;
            for (unsigned k = 0; k < lcol; k++) {
                m_mat[i][j] += (*lmat)[i][k] * (*rmat)[k][j];
            }
        }
    }
}

template <typename T>
template <typename F, typename E>
ProductExpr<T>::ProductExpr(const ProductExpr<E> &lhs, const BaseMatrix<F> &rhs)
{
    unsigned lrow = lhs.m_mat.size();

    std::shared_ptr<std::vector<std::vector<F>>> rmat = rhs.GetMatrix();
    unsigned rrow = rhs.get_rows();
    unsigned rcol = rhs.get_cols();

    m_mat.resize(lrow);
    for (unsigned i = 0; i < lrow; i++) {
        m_mat[i].resize(rcol);
    }

    for (unsigned i = 0; i < lrow; i++) {
        for (unsigned j = 0; j < rcol; j++) {
            m_mat[i][j] = 0;
            for (unsigned k = 0; k < rrow; k++) {
                m_mat[i][j] += lhs.m_mat[i][k] * (*lmat)[k][j];
            }
        }
    }
}

template <typename T>
template <typename F, typename E>
ProductExpr<T>::ProductExpr(const BaseMatrix<F> &lhs, const ProductExpr<E> &rhs)
{
    std::shared_ptr<std::vector<std::vector<T>>> lmat = lhs.GetMatrix();
    unsigned lrow = lhs.get_rows();
    unsigned lcol = lhs.get_cols();

    unsigned rcol = rhs.m_mat[0].size();

    m_mat.resize(lrow);
    for (unsigned i = 0; i < lrow; i++) {
        m_mat[i].resize(rcol);
    }

    for (unsigned i = 0; i < lrow; i++) {
        for (unsigned j = 0; j < rcol; j++) {
            m_mat[i][j] = 0;
            for (unsigned k = 0; k < lcol; k++) {
                m_mat[i][j] += (*lmat)[i][k] * rhs.m_mat[k][j];
            }
        }
    }
}

template <typename T>
template <typename F, typename E>
ProductExpr<T>::ProductExpr(const ProductExpr<E> &lhs,
    const ProductExpr<F> &rhs)
{

    unsigned lrow = lhs.m_mat.size();
    unsigned rrow = rhs.m_mat.size();
    unsigned rcol = rhs.m_mat[0].size();

    m_mat.resize(lrow);
    for (unsigned i = 0; i < lrow; i++) {
        m_mat[i].resize(rcol);
    }

    for (unsigned i = 0; i < lrow; i++) {
        for (unsigned j = 0; j < rcol; j++) {
            m_mat[i][j] = 0;
            for (unsigned k = 0; k < rrow; k++) {
                m_mat[i][j] += lhs.m_mat[i][k] * rhs.m_mat[k][j];
            }
        }
    }
}
template <typename T>
ProductExpr<T>::ProductExpr(const unsigned &rows, const unsigned &cols)
{
    m_mat.resize(rows);
    for (unsigned i = 0; i < rows; i++) {
        m_mat[i].resize(cols);
    }
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            m_mat[i][j] = 0;
        }
    }
}

} // Matrix