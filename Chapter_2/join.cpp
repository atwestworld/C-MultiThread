/*
    join特殊情况：主线程抛出异常导致join没有执行
    解决方法：使用RAII手法 or 异常处理代码中join
    通过RAII手法，可以保证线程在任何情况下都会被正确地join
    RAII：私有化拷贝构造函数和赋值运算符，避免通过现有对象创建新对象导致多个RAII实例管理相同的线程
*/

#include <iostream>
#include <thread>

using namespace std;


struct func
{
  int& i;
  func(int& i_) : i(i_) {}
  void operator() ()
  {
    for (unsigned j=0 ; j<10; ++j)
    {
      cout << i << endl;           // 潜在访问隐患：悬空引用
    }
  }
};


class thread_guard
{
    std::thread& t;
  public:
    thread_guard(std::thread& t_) : t(t_) {}
    ~thread_guard()
    {
      if (t.joinable())   // 1
      {
        t.join();       // 2
      }
    }

    // 拷贝构造函数和赋值运算符，通过现有对象创建新对象
    thread_guard(thread_guard const&)=delete; // 需要将拷贝构造函数和赋值运算符声明为私有，防止编译器自动生成，因为这两个函数会导致多个thread_guard对象管理同一个线程，从而导致程序崩溃
    thread_guard& operator=(thread_guard const&)=delete;
};

int main() {
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    
    // do_something_in_current_thread();    抛出异常导致后续 join 没有执行，但是通过RAII调用析构函数，线程依旧会被加入到原始线程中
}   // 4

/*
    当线程执行到④处时，局部对象就要被逆序销毁了。因此，thread_guard对象g是第一个被销毁的，这时线程在析构函数中被加入②到原始线程中。
    即使do_something_in_current_thread抛出一个异常，这个销毁依旧会发生。
*/




