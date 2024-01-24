/*
    将函数对象或成员函数与其参数绑定，以创建一个可调用的对象。
*/

#include <functional>
#include <iostream>

void myFunction(int a, int b, int c) {
    std::cout << a << " " << b << " " << c << std::endl;
}

int main() {
    // 使用 std::bind 绑定参数
    auto myBind = std::bind(myFunction, 1, std::placeholders::_1, 3);

    /*
        占位符：
        std::placeholders::_1、std::placeholders::_2 等是占位符，用于指定绑定的位置。它们对应于被绑定函数的参数位置。
    */

   /*
    成员函数的绑定：
    std::bind 也可以用于绑定成员函数。例如，std::bind(&ClassName::memberFunction, object, _1, _2) 绑定了一个对象的成员函数。
绑定到引用：

std::ref 可以用于将参数绑定到引用，以确保对参数的更改在绑定后仍然有效。
   */

    // 调用绑定的函数
    myBind(2);  // 输出: 1 2 3

    return 0;
}
