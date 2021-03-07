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

    std::shared_ptr<std::vector<std::vector<int>>> x = a.GetMatrix();
    cout << (*x).at(0).at(0) << endl;
    cin.get();
    return 0;
}