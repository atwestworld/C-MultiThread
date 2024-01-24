/*
    线程创建的几个步骤
*/
#include <iostream>
#include <thread>       // std::thread

using namespace std;

void thread_function() {    // thread function
    int i = 1;
    i++;

    cout << "thread function\n";
}

int main() {
    std::thread t(thread_function); // t starts running
    t.join();   // main thread waits for the thread t to finish
}
