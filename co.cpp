#include <experimental/coroutine>

std::experimental::suspend_always yield_value(const char *value);

int myCoroutine() {
  co_yield "Hello,";
  co_yield "World";
  co_return "!";
}

int main() {
  auto x = myCoroutine();
  x.next();
  return 0;
}
