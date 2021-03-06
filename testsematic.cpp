#include <iostream>
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <memory>
#include <string>
#include <cstdlib>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <type_traits>

template <class T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
#else
                nullptr,
#endif
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

using namespace std;

template <typename T>
class BM
{
public:
    BM(T in) : a(in) {}
    T a;
};

template <typename T>
class PE
{
public:
    // template <typename F>
    // PE(BM<T> A, BM<F> B) {
    //     C = A.a + B.a;
    //     cout <<  type_name<decltype(A)>() << endl;
    //     cout <<  type_name<decltype(B)>() << endl;
    //     cout <<  type_name<decltype(C)>() << endl;
    // }

    template <typename F, typename E>
    PE(BM<E> A, BM<F> B) {
        C = A.a + B.a;
        cout << type_name<decltype(A)>() << endl;
        cout << type_name<decltype(B)>() << endl;
        cout << type_name<decltype(C)>() << endl;
    }

    T C;
};

// template <typename X, typename F, typename T>
// inline PE<X> operator*(BM<T> A, BM<F> B) {
//     return PE<X>(A, B);
// }

template <typename F, typename T>
inline auto operator*(BM<T> A, BM<F> B) {
    return PE<float>(A, B);
}
template <typename T>
inline auto operator*(BM<T> A, BM<T> B) {
    return PE<T>(A, B);
}

template <typename T, typename F>
inline PE<T> operator+(BM<T> A, BM<F> B) {
    return PE<T>(A, B);
}

// 传一个 A是int B是float 看C是啥
int main() {
    BM<int> A(1);
    BM<float> B(1.f);
    // PE<int> C(A, B);
    PE<double> C(A, B); // OK
    PE<int> D(A, B); //OK
    PE<int> E = A + B; //ok
    PE<float> F = B + B; //ok
    cout << "--------------" << endl;
    // PE<float> G = A * B; // not ok
    A * B; // not ok
    A * A; // not ok

    cin.get();
    return 0;
}
// template <typename T>
// template <typename T>
// template <typename T>
// template <typename T>
// template <typename T>
// template <typename T>
// template <typename T>