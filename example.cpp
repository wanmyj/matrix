#include <iostream>
#include <Dense_Matrix.h>

using namespace Matrix;
using namespace std;
int main() {
    DenseMatrix<int> a{{1}};
    std::shared_ptr<std::vector<std::vector<int>>> x = a.GetMatrix();
    cout << (*x).at(0).at(0) << endl;
    cin.get();
    return 0;
}