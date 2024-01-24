/*
    thread 和 bind 中必须使用 std::ref() 来传递引用，否则会被当做值传递
*/
#include <iostream>
#include <functional>
#include<vector>

using namespace std;

// std::ref主要是考虑函数式编程（如std::bind）在使用时，是对参数直接拷贝，而不是引用
void f(int& a, int& b, int& c)      // 1
{
    cout << "in function a = " << a << "  b = " << b << "  c = " << c << endl;
    cout << "in function a = " << &a << "  b = " << &b << "  c = " << &c << endl;
    a += 1;
    b += 10;
    c += 100;
}

int main() {

    int n1 = 1, n2 = 10, n3 = 100;
    int& r1 = n1;       // 2
    int& r2 = n2;

    // 将函数对象或成员函数与其参数绑定，以创建一个可调用的对象。f1中相当于已经有了r1, r2两个数, 以及n3的引用
    function<void()> f1 = bind(f, r1, r2, ref(n3));		// 3
    // 前两个参数即便是引用类型，bind 传入的还是其值的拷贝，第三个参数传入 reference_wrapper 对象，该对象可隐式的转换为值的引用

    f1();
    cout << "out function a = " << n1 << "  b = " << n2 << "  c = " << n3 << endl;
    cout << "out function a = " << &n1 << "  b = " << &n2 << "  c = " << &n3 << endl;
    f1();           
    cout << "out function a = " << n1 << "  b = " << n2 << "  c = " << n3 << endl;
    cout << "out function a = " << &n1 << "  b = " << &n2 << "  c = " << &n3 << endl;
    return 0;
}
