#ifndef __PRODUCT_EXPR_H
#define __PRODUCT_EXPR_H

#include <vector>
#include <memory>
#include <type_traits>

namespace Matrix {

class Base {};

template <typename>
struct is_matrix_expr : public std::false_type {};
template <typename T>
class BaseMatrix;

template <typename T>
class ProductExpr : Base
{
public:
    std::vector<std::vector<T>> m_mat;
    typedef T   datatype;
public:
    template <typename F, typename E>
    ProductExpr(const BaseMatrix<E> &lhs, const BaseMatrix<F> &rhs)
    {
        if (lhs.get_cols() != rhs.get_rows()) {
            throw std::invalid_argument("two matrices are NOT multipliable");
        }
        std::shared_ptr<std::vector<std::vector<E>>> lmat = lhs.GetMatrix();
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

    template <typename F, typename E>
    ProductExpr(const ProductExpr<E> &lhs, const BaseMatrix<F> &rhs)
    {
        if (lhs.m_mat[0].size() != rhs.get_rows()) {
            throw std::invalid_argument("two matrices are NOT multipliable");
        }
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
                    m_mat[i][j] += lhs.m_mat[i][k] * (*rmat)[k][j];
                }
            }
        }
    }

    template <typename F, typename E>
    ProductExpr(const BaseMatrix<F> &lhs, const ProductExpr<E> &rhs)
    {
        if (lhs.get_cols() != rhs.m_mat.size()) {
            throw std::invalid_argument("two matrices are NOT multipliable");
        }
        std::shared_ptr<std::vector<std::vector<F>>> lmat = lhs.GetMatrix();
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

    template <typename F, typename E>
    ProductExpr(const ProductExpr<E> &lhs, const ProductExpr<F> &rhs)
    {
        if (lhs.m_mat[0].size() != rhs.m_mat.size()) {
            throw std::invalid_argument("two matrices are NOT multipliable");
        }
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

    ProductExpr(const unsigned &rows, const unsigned &cols)
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

};


template <typename T>
struct is_matrix_expr<ProductExpr<T>> : public std::true_type {};
template <typename T>
struct is_matrix_expr<BaseMatrix<T>> : public std::true_type {};


template <typename E, typename F,
    class = typename std::enable_if<std::is_base_of<Base, E>::value &&
                                    std::is_base_of<Base, F>::value>::type,
    class = typename std::enable_if<
        std::is_same<typename std::remove_cv<E>::type::datatype,
                     typename std::remove_cv<F>::type::datatype>::value>::type
>
inline auto operator*(const E &lhs, const F &rhs)
{
    return  ProductExpr<typename std::remove_cv<F>::type::datatype>(lhs, rhs);
}

template <typename E, typename F,
    typename std::enable_if<std::is_base_of<Base, E>::value &&
                            std::is_base_of<Base, F>::value>::type* = nullptr,
    class = typename std::enable_if<
        !std::is_same<typename std::remove_cv<E>::type::datatype,
                      typename std::remove_cv<F>::type::datatype>::value>::type
>
inline auto operator*(const E &lhs, const F &rhs)
{
    return  ProductExpr<double>(lhs, rhs);
}

// Type Diff Matrix/Scalar operations
template <typename T, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
ProductExpr<double> operator*(const BaseMatrix<T> &lhs, const F &rhs)
{
    std::shared_ptr<std::vector<std::vector<T>>> originMat = lhs.GetMatrix();
    unsigned rows = lhs.get_rows();
    unsigned cols = lhs.get_cols();

    ProductExpr<double> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = (*originMat)[i][j] * rhs;
        }
    }
    return res;
}

// Type Diff Scalar/Matrix operations
template <typename T, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
ProductExpr<double> operator*(const F &lhs, const BaseMatrix<T> &rhs)
{
    std::shared_ptr<std::vector<std::vector<T>>> originMat = rhs.GetMatrix();
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    ProductExpr<double> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = (*originMat)[i][j] * lhs;
        }
    }
    return res;
}

// Type Same Matrix/Scalar operations
template <typename T>
ProductExpr<T> operator*(const BaseMatrix<T> &lhs, const T &rhs)
{
    std::shared_ptr<std::vector<std::vector<T>>> originMat = lhs.GetMatrix();
    unsigned rows = lhs.get_rows();
    unsigned cols = lhs.get_cols();

    ProductExpr<T> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = (*originMat)[i][j] * rhs;
        }
    }
    return res;
}

// Type Same Scalar/Matrix operations
template <typename T>
ProductExpr<T> operator*(const T &lhs, const BaseMatrix<T> &rhs)
{
    std::shared_ptr<std::vector<std::vector<T>>> originMat = rhs.GetMatrix();
    unsigned rows = rhs.get_rows();
    unsigned cols = rhs.get_cols();

    ProductExpr<T> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = (*originMat)[i][j] * lhs;
        }
    }
    return res;
}

// Type Diff ProductExpr/Scalar operations
template <typename T, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
ProductExpr<double> operator*(const ProductExpr<T> &lhs, const F &rhs)
{
    unsigned rows = lhs.m_mat.size();
    unsigned cols = lhs.m_mat[0].size();

    ProductExpr<double> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = lhs.m_mat[i][j] * rhs;
        }
    }
    return res;
}

// Type Diff Scalar/ProductExpr operations
template <typename T, typename F,
    typename std::enable_if<std::is_arithmetic<F>::value>::type* = nullptr>
ProductExpr<double> operator*(const F &lhs, const ProductExpr<T> &rhs)
{
    unsigned rows = rhs.m_mat.size();
    unsigned cols = rhs.m_mat[0].size();

    ProductExpr<double> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = rhs.m_mat[i][j] * lhs;
        }
    }
    return res;
}

// Type Same ProductExpr/Scalar operations
template <typename T>
ProductExpr<T> operator*(const ProductExpr<T> &lhs, const T &rhs)
{
    unsigned rows = lhs.m_mat.size();
    unsigned cols = lhs.m_mat[0].size();

    ProductExpr<T> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = lhs.m_mat[i][j] * rhs;
        }
    }
    return res;
}

// Type Same Scalar/ProductExpr operations
template <typename T>
ProductExpr<T> operator*(const T &lhs, const ProductExpr<T> &rhs)
{
    unsigned rows = rhs.m_mat.size();
    unsigned cols = rhs.m_mat[0].size();

    ProductExpr<T> res(rows, cols);
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < cols; j++) {
            res.m_mat[i][j] = rhs.m_mat[i][j] * lhs;
        }
    }
    return res;
}

} // Matrix

#endif