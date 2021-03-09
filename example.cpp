#include <iostream>
#include <Dense_Matrix.h>
#include <Diag_Matrix.h>

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
    cout << "print f Tranpose" << endl;
    f.PrintMat();

    DenseMatrix<int> g{{1, 2, 3},{3, 2, 1}, {2, 2, 2}};
    DenseMatrix<float> h{{1.2},{3.7, 1}, {2, 2}};
    DenseMatrix<int> i{{1},{3}};
    DenseMatrix<float> k{{2.34}};

    cout << "print f = g * h * i * k" << endl;
    f = g * h * 3 * i * k;
    f.PrintMat();

    a = 3 * b;
    a = b * 3;
    a = 3 * b * 3;
    cout << "print a = 3 * b * 3" << endl;
    a.PrintMat();
    a = 3 * (b * 3);
    cout << "print a = 3 * (b * 3)" << endl;
    a.PrintMat();

    f = 3 * b;
    f = b * 3;
    f = 3 * b * 3;
    cout << "print f = 3 * b * 3" << endl;
    f.PrintMat();
    f = 3 * (b * 3);    
    cout << "print f = 3 * (b * 3)" << endl;
    f.PrintMat();

    f = 3 * h;
    f = h * 3;
    f = 3 * h * 3;
    cout << "print f = 3 * h * 3" << endl;
    f.PrintMat();
    f = 3 * (h * 3);    
    cout << "print f = 3 * (h * 3)" << endl;
    f.PrintMat();
    
    try {
        f = f * f.Transpose(); //this is wrong
        cout << "f = f * f.Transpose()" << endl;
        f.PrintMat();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    cout << "-----------------------" << endl;
    DiagMatrix<int> da{1, 2, 3};
    cout << "print da{1, 2, 3}" << endl;
    da.PrintMat();

    vector<int> v{1, 2, 3};
    DiagMatrix<int> db{v};
    cout << "print db{v}" << endl;
    db.PrintMat();

    DiagMatrix<int> dc = da * db;
    cout << "print dc{v}" << endl;
    dc.PrintMat();

    vector<float> v2{1, 2.02, 3};
    DiagMatrix<float> df{v2};
    DiagMatrix<double> dd = da * df;
    cout << "print dc{v}" << endl;
    dd.PrintMat();

    f = b * dd;
    cout << "print f = b * dd" << endl;
    f.PrintMat();

    f = da * 3.6;
    cout << "print f = da * 3.6" << endl;
    f.PrintMat();

    f = 4.8 * da;
    cout << "print f = 4.8 * da" << endl;
    f.PrintMat();

    cin.get();
    return 0;
}