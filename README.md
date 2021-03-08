# wanmyj::Matrix - The C++ Linear Algebra Library (in development) #

This repo is for the interview project of the folowing requirements

Please design and implement a Matrix family. The family should include at least following matrix types:
- Dense matrix, which means most of the items in that matrix are not zero.
- Sparse matrix. You can find the definition for it here: http://en.wikipedia.org/wiki/Sparse_matrix
- Diagonal matrix. You can find the definition for it here: http://en.wikipedia.org/wiki/Diagonal_matrix  
 

The operations for the matrix should at least include (prioritized):
- Multiply (with another Matrix or a scalar value)
- Transpose
 

Tasks: (prioritized)
- Please design the inheritance hierarchy for this Matrix family. The design should make it as easy as possible to add one more Matrix type into the family.
- Please design a good data structure for each matrix so that it costs least memory and has best performance for the operations.
- Please implement the classes in template (C++).
- Please try your best to make the operations have the best performance. 
- Please write also small test program to verify the operations.

## Overview

The realization provides:
  + Basic initializer_list initialization of matrix
  + Basic matrix transpose operation
  + Basic matrix multiplication operation
  + Continuous multiplication operation
  + Cross-datatype multiplication operation (e.g. Matrix\<int\> * Matrix\<float\>)
  + Cross-matrixtype multiplication operation (e.g. DenseMatrix\<int\> * DiagMatrix\<int\>)

## Test Environment

    c++11 standard
    g++ 6.3.0
    Ubuntu 18.04
   
## Compile Cmd

```sh
g++ -std=c++11 -I. example.cpp
```

## Example program
`example.cpp`:
```c
#include <iostream>
#include <Dense_Matrix.h>

using namespace Matrix;
using namespace std;
int main() {
    DenseMatrix<int> a{{1}};
    cout << "print a" << endl;
    a.PrintMat();

    DenseMatrix<int> b{{1, 2, 3},{3, 2, 1}, {2, 2, 2}};
    cout << "print b" << endl;
    b.PrintMat();

    DenseMatrix<int> c{{1},{3, 1}, {2, 2}};
    cout << "print c" << endl;
    c.PrintMat();

    DenseMatrix<int> d = b * c;
    cout << "print d" << endl;
    d.PrintMat();

    DenseMatrix<double> f = b * c;
    cout << "print f" << endl;
    f.PrintMat();

    f.Transpose();
    cout << "print f Transpose" << endl;
    f.PrintMat();

    DenseMatrix<int> g{{1, 2, 3},{3, 2, 1}, {2, 2, 2}};
    DenseMatrix<float> h{{1.2},{3.7, 1}, {2, 2}};
    DenseMatrix<int> i{{1},{3}};
    DenseMatrix<float> k{{2.34}};

    cout << "print f = g * h * i * k" << endl;
    f = g * h * i * k;
    f.PrintMat();

    cin.get();
    return 0;
}
```
output:

```sh
print a
Mat = 
1 

print b
Mat = 
1 2 3 
3 2 1 
2 2 2 

print c
Mat = 
1 0 
3 1 
2 2 

print d
Mat = 
13 8 
11 4 
12 6 

print f
Mat = 
13 8 
11 4 
12 6 

print f Tranpose
Mat = 
13 11 12 
8 4 6 

print f = g * h * i * k
Mat = 
90.324 
58.5 
74.412 
```

## Reference
<https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Header-File/>

<https://www.quantstart.com/articles/Matrix-Classes-in-C-The-Source-File/>