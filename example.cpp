#include <iostream>
#include <Dense_Matrix.h>
#include <Diag_Matrix.h>
#include <Sparse_Matrix.h>

using namespace Matrix;
using namespace std;
int main() {
    // dense matrix initialization (vector initializer_list)
    cout << "dense matrix initialization" << endl;

    DenseMatrix<int> Da{{1}};
    cout << "print Da" << endl;
    Da.PrintMat();

    DenseMatrix<int> Db{{1, 2, 3},{3, 1}, {2, 2, 2}};
    cout << "print Db" << endl;
    Db.PrintMat();
    
    std::vector<std::vector<double>> DVc = {
        {1, 2, 3, 4},
        {2}, 
        {5, 2, 1} 
    };
    DenseMatrix<double> Dc(DVc);
    cout << "print Dc" << endl;
    Dc.PrintMat();

    // dense matrix transpose
    Db.Transpose();
    cout << "print Db transpose" << endl;
    Db.PrintMat();

    // dense matrix multiply (Tscalar * Tmatrix, Tscalar * Fmatrix, Tmatrix * Tmatrix, Tmatrix * Fmatrix)
    cout << "dense matrix multiply\n" << endl;
    DenseMatrix<int> Di = Db * 3;
    cout << "print Di = Db * 3" << endl;
    Di.PrintMat();

    Di = 3 * Di;
    cout << "print Di = 3 * Di" << endl;
    Di.PrintMat();

    DenseMatrix<double> Dj = Dc * 3;
    cout << "print Dj = Dc * 3" << endl;
    Dj.PrintMat();

    Dj = 3.1 * Da;
    cout << "print Dj = 3.1 * Da" << endl;
    Dj.PrintMat();


    // diag matrix initialization (vector initializer_list)
    cout << "diag matrix initialization" << endl;
    DiagMatrix<int> da{1, 2, 3};
    cout << "print da{1, 2, 3}" << endl;
    da.PrintMat();

    vector<float> dvb{1, 2.4, 3};
    DiagMatrix<float> db{dvb};
    cout << "print db{dvb}" << endl;
    db.PrintMat();

    // diag matrix transpose
    db.Transpose();
    cout << "print db transpose" << endl;
    db.PrintMat();

    // diag matrix multiply (Tscalar * Tmatrix, Tscalar * Fmatrix, Tmatrix * Tmatrix, Tmatrix * Fmatrix)
    cout << "diag matrix multiply\n" << endl;

    DiagMatrix<int> di = da * 5;
    cout << "print di = da * 5" << endl;
    di.PrintMat();
    
    di = 12 * di;
    cout << "print di = 12 * di" << endl;
    di.PrintMat();

    DiagMatrix<double> dj = da * 1.3;
    cout << "print di = da * 5" << endl;
    dj.PrintMat();

    dj = 3.2 * db ;
    cout << "print dj = 3.2 * db" << endl;
    dj.PrintMat();

    // sparse matrix initialization (vector initializer_list)
    cout << "sparse matrix initialization" << endl;

    SparseMatrix<int> sa{3, 4, {{1, 2, 3}, {2, 2, 4}}};
    cout << "print sa" << endl;
    sa.PrintMat();

    std::vector<unsigned> svb1{2, 2, 1, 4};
    std::vector<unsigned> svb2{1, 2, 3, 4};
    std::vector<float> sva3{1.3, 1, 4, 8};
    SparseMatrix<float> sb(5, 5, svb1, svb2, sva3);
    cout << "print sb" << endl;
    sb.PrintMat();

    // sparse matrix transpose
    cout << "sparse matrix transpose\n" << endl;
    sb.Transpose();
    cout << "print sb transpose" << endl;
    sb.PrintMat();

    // sparse matrix multiply (Tscalar * Tmatrix, Tscalar * Fmatrix, Tmatrix * Tmatrix, Tmatrix * Fmatrix)
    cout << "diag matrix multiply\n" << endl;
    SparseMatrix<int> si = sa * 3;
    cout << "print si = sa * 3" << endl;
    si.PrintMat();

    si = 4 * si;
    cout << "print si = 4 * si" << endl;
    si.PrintMat();

    SparseMatrix<double> sj = sb * 3;
    cout << "print sj = sb * 3" << endl;
    sj.PrintMat();

    sj = 2.7 * sa;
    cout << "print sj = 2.7 * sa" << endl;
    sj.PrintMat();

    // dense(T/double) = scalar * sparse * (sparse * scalar)
    DenseMatrix<double> Ds  = 3 * ( sb * 1.2);
    cout << "print Ds  = 3 * ( sb * 1.2)" << endl;
    Ds.PrintMat();

    DenseMatrix<double> Dm  = 3 * sb * ( sb * 1.2);
    cout << "print Dm  = 3 * sb * ( sb * 1.2)" << endl;
    Dm.PrintMat();

    // dense(T/double) = sparse * (diag * scalar)
    DiagMatrix<int> dn{1, 2, 3, 4, 5};
    DenseMatrix<double> Dn  = 3.2 * sb * ( dn * 2);
    cout << "print Dn  = 3.2 * sb * ( dn * 2)" << endl;
    Dn.PrintMat();

    // dense(T/double) = diag * (scalar * (diag * scalar) * sparse.transpose)
    DenseMatrix<double> Do  = dn * (3 * (dn * 2.1) * sb.Transpose());
    cout << "print Do  = dn * (3 * (dn * 2.1) * sb.Transpose())" << endl;
    Do.PrintMat();

    // exception test
    cout << "-----------------------" << endl;
    try {
        Dc = Dc * Dc.Transpose(); //this is wrong
        cout << "Dc = Dc * Dc.Transpose()" << endl;
        Dc.PrintMat();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    cin.get();
    return 0;
}