#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>

#include "final_action.hpp"
#include "threadpool.h"
using namespace std;

// std::future提供了一种用于访问异步操作结果的机制。
// std::future所引用的共享状态不能与任何其它异步返回的对象共享(与std::shared_future相反)(
//一个future是一个对象，它可以从某个提供者的对象或函数中检索值，如果在不同的线程中，则它可以正确地同步此访问

/*
1.future退出阻塞只会在绑定async场景下，其他都不会触发
2. 使用lambda引用捕捉参数时候一定要注意对象生命周期

本质原因是因为：我们有部分代码分支会提前退出，导致局部变量提前释放，解决方法就是老生常谈的RAII
*/
ThreadPool pool(4);
//
void Func(std::string& name) {
  std::vector<std::future<void> > results;
  //
  results.emplace_back(pool.enqueue([&]() {
      // 可能是一个非常耗时的操作
    cout << "------custom func"
         << "------>" << name << endl;
    sleep(2);
  }));
  auto func = final_action([&results]() {
    for (auto&& item : results) {
      cout << "------start wait"
           << "------" << endl;
      item.wait();
      cout << "------end wait"
           << "------" << endl;
    }
  });
 // 其他人添加的代码
  {
    cout << "------other func handle------" << endl;
    return;
  }

//   for (auto&& item : results) {
//     cout << "------start wait"
//          << "------" << endl;
//     item.wait();
//     cout << "------end wait"
//          << "------" << endl;
//   };

  
}

bool is_prime(int x) {
  sleep(x);
  return true;
}
void FuncAsync() {
  cout << "------enter in func FuncAsync------" << endl;
  {
    std::future<bool> fut = std::async(is_prime, 2);
    cout << "------enter finish func FuncAsync------" << endl;
  }
  cout << "------enter out func FuncAsync------" << endl;
}
int main() {
   //FuncAsync();
  cout << "------main func start"
       << "------" << endl;
  {
    std::string global_str = "feature_states_repo";
    Func(global_str);
  }

  cout << "------main func end"
       << "------" << endl;
  return 0;
}
