#ifndef __BASE_MATRIX_H
#define __BASE_MATRIX_H

#include "Product_Expr.h"
#include <memory>
namespace Matrix {

template <typename T>
class BaseMatrix
{
protected:
    unsigned m_rows;
    unsigned m_cols;

public:
    BaseMatrix() : m_rows(0), m_cols(0) {};
    BaseMatrix(const BaseMatrix<T> &rhs) = default; //copy contrructor
    BaseMatrix(BaseMatrix<T> &&rhs) = default;      //move contrructor
    virtual ~BaseMatrix();

    // Operator overloading, for "standard" mathematical matrix operations
    virtual BaseMatrix<T>& operator=(const BaseMatrix<T> &rhs);
    virtual BaseMatrix<T>& operator=(BaseMatrix<T> &&rhs);

    virtual BaseMatrix<T> Transpose();

    // Access the individual elements
    virtual std::vector<T>& operator[](const unsigned &row) = 0;
    virtual const std::vector<T>& operator[](const unsigned &row) const;

    // Access the row and column sizes
    unsigned get_rows() const;
    unsigned get_cols() const;

    // Get the full matrix
    virtual std::shared_ptr<std::vector<std::vector<T>>> GetMatrix() = 0;
};

} // Matrix
#include "Base_Matrix.cpp"

#endif

// 基类矩阵之间乘法计算的结果放入ProductExpr
// 基类矩阵与数字乘法的结果也存入ProductExpr
// 基类不提供数据结构,所有派生类需要设计自己的数据结构
// 基类不提供任何方式的自定义构造函数，所有的自定义构造函数必须重载
// 
// GetMatrix()必须重载 返回一个智能指针，指向一片堆内存
// Transpose必须重载
// 同种类矩阵相乘，派生类与数字乘法的结果可以重载，不重载只返回DenseMatrix
// mat[][] 修改元素 只有DENSE SPARSE允许 DIAG触发exception 
//      https://stackoverflow.com/questions/24609872/delete-virtual-function-from-a-derived-class
// mat[][] const 获取元素 都允许，Base实现，派生类重载
// 合法矩阵乘法引入except判断
// *= ProductExpr定义 无返回  可重载 DD DS SD SS （暂时不实现）
// 矩阵的赋值操作参考RTTI方式
//      https://stackoverflow.com/questions/669818/virtual-assignment-operator-c
// ProductExpr可以设置成BaseMatrix的friend类
// 要注意 整数翻转
// 
//
// 测试要点
// 