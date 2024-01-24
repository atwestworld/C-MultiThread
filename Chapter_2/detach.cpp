/*
    detach中需要注意：
    新线程中需要访问的数据在运行时必须存在
*/

#include <iostream>
#include <thread>

#include <unistd.h>

class ThreadObject{
    private:
        int &m_i;
    public:
        ThreadObject(int &i):m_i(i) {}
        void operator()() {
            sleep(1);
            try
            {
                std::cout << "the val is " << m_i << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
};


int main() {
    int local_val = 10;
    ThreadObject t(local_val);
    std::thread t1(t);
    t1.detach();
    sleep(1);
    return 0;       // local_val被销毁，线程中的引用失效，程序崩溃
}

