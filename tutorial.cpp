#include <boost/coroutine2/all.hpp>
#include <functional>
#include <iostream>
#include <vector>

namespace coroutines = boost::coroutines2;
template <typename T> using coroutine = boost::coroutines2::coroutine<T>;

void co_push_fun(coroutine<int>::push_type &yield, int v) {
  for (int i = 0; i < v; i++) {
    std::cout << "coroutine pushing: " << i << std::endl;
    yield(i);
    std::cout << "coroutine pushed: " << i << std::endl;
  }
}

void co_pull_fun(coroutine<int>::pull_type &yield) {
  int round = 0;
  while (yield) {
    std::cout << "coroutine pulled: " << round << std::endl;
    auto i = yield.get();
    std::cout << "coroutine pulled value: " << i << std::endl;
    yield();
    // logic after yield
    std::cout << "coroutine pulling: " << round << std::endl;
    round++;
  }
}

void test_co_pull_fun() {
  coroutine<int>::pull_type resume{
      std::bind(co_push_fun, std::placeholders::_1, 6)};
  while (resume) {
    std::cout << "caller while: " << resume.get() << std::endl;
    resume();
  }
  coroutine<int>::pull_type resume2{
      std::bind(co_push_fun, std::placeholders::_1, 7)};
  for (int c : resume2) {
    std::cout << "caller for: " << c << std::endl;
  }
}

void test_co_push_fun() {
  coroutine<int>::push_type sink{co_pull_fun};
  std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i : numbers) {
    std::cout << "sinking: " << i << std::endl;
    sink(i);
    std::cout << "sinked: " << i << std::endl;
  }
}

int main() {
  test_co_push_fun();
  return 0;
}
