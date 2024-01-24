/*
    线程创建方式：函数 or 函数对象 or lambda
*/

#include <iostream>
#include <thread>

// 函数
void thread_function() {
    std::cout << "thread function\n";
}

// 函数对象
class DisplayThread {
    public:
    void operator()() {
        std::cout << "Display Thread Executing\n";
    }
};

int main() {
    std::thread t1(thread_function);    // function pointer
    // std:: thread t2(DisplayThread());   最令人烦恼的解析，这里不是创建线程，而是声明了一个函数t2，返回值是std::thread，参数是一个函数指针，函数指针的返回值是DisplayThread，参数是一个函数指针，函数指针的返回值是void，参数为空
    std::thread t2((DisplayThread())); 
    std::thread t3{DisplayThread()};    // uniform initialization
    DisplayThread dt;
    std::thread t4(dt);                 // copy of dt in t4

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

