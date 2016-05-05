#include <iostream>
#include <thread>
#include "Promise.h"

int main() {
  Promise<int> pro = Promise<int>([](Promise<int>::Func resolve, Promise<int>::Func reject) {
    std::thread t([&]() {
      resolve(1);
    });
    t.join();
  });

  pro.then([&](int d) {
    std::cout << "thread" << d << std::endl;
    std::cout << "main" << std::endl;
  }, NULL);

  return 0;
}
