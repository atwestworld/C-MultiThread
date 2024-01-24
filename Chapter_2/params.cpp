/* 参数为指向动态资源的指针 */

#include <iostream>
#include <thread>

using namespace std;

// 线程入口函数
void f(int i,string const& s) {
    for (int j = 0; j<i; ++j) {
        cout << s << endl;
    }
}

void oops(int some_param)
{
  char buffer[1024];    // 1
  sprintf(buffer, "%i",some_param);
  thread t(f,3, buffer);    // 2 传入的是buffer的拷贝，而不是buffer本身，且buffer生命周期短，导致问题
//   thread t(f,3, to_string(some_param));    
  t.detach();
}

int main() {
    oops(100);

    /* 当主线程结束时，整个进程也会结束，这包括所有的子线程，无论它们是否已经完成了它们的任务 */
    this_thread::sleep_for(chrono::seconds(1));
}
