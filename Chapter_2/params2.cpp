/* 参数为引用，需要使用 ref */
/* 入口函数为类的成员函数，需要传入参数实例化*this*/

#include <iostream>
#include <thread>

using namespace std;
/*

void update_data_for_widget(widget_id w,widget_data& data); // 1
void oops_again(widget_id w)
{
  widget_data data;
  std::thread t(update_data_for_widget,w,data); // 2  
    -》 std::thread t(update_data_for_widget,w,std::ref(data));
  display_status();
  t.join();
  process_widget_data(data); // 3
}

*/

class X
{
public:
  void do_lengthy_work(int);
};
X my_x;
int num(0);
std::thread t(&X::do_lengthy_work, &my_x, num);

