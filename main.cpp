#include <boost/coroutine2/all.hpp>
#include <functional>
#include <iostream>

namespace coroutines = boost::coroutines2;
template <typename T> using coroutine = boost::coroutines2::coroutine<T>;

void myCoroutine(coroutine<void>::push_type &yield) {
  std::cout << "coroutine: Hello" << std::endl;
  yield();
  std::cout << "coroutine: World" << std::endl;
  yield();
  std::cout << "coroutine: Goodbye" << std::endl;
  yield();
  std::cout << "coroutine: Everyone" << std::endl;
}

template <typename T> class Enumerator {
public:
  explicit Enumerator(std::function<T> fn){

  };

  ~Enumerator() { delete co; }

  void Resume() {}
  void Current() {}
  void Reset() {}
  void Pause() {}
  void Reverse() {}

private:
  coroutine<void>::pull_type *co;
};

int intCo(coroutine<int>::push_type &yield) {
  static int myInt = 0;
  while (myInt < 5) {
    yield(++myInt);
  }
  yield(-1);
}

class MyClass {
public:
  MyClass() {}
  ~MyClass() = default;

  void Update() { pullC(); }

  void EnumerateEnemies(coroutine<int>::push_type &yield) {
    while (true) {
      if (_currentEnemySpawn < _maxEnemies) {
        _currentEnemySpawn++;
      }
      yield(_currentEnemySpawn);
    }
  }

  void ResetEnumeration() { _currentEnemySpawn = -1; }

  int CurrentEnemy() { return pullC.get(); }

private:
  // NOTE: with class member
  coroutine<int>::pull_type pullC{
      std::bind(&MyClass::EnumerateEnemies, this, std::placeholders::_1)};
  // NOTE: with lambda
  // coroutine<int>::pull_type pull{[&](auto &yield) {
  //   int _max = 5;
  //   int _current = 0;
  //   for (;;) {
  //     if (_current < 5) {
  //       std::cout << "incrementing _currentEnemySpawn from " << _current
  //                 << " to " << _current + 1 << std::endl;
  //       _current++;
  //     }
  //     yield(_current);
  //   }
  // }};
  int _currentEnemySpawn{0};
  int _maxEnemies{5};
};

int main(int, char **) {
  std::cout << "Before construction" << std::endl;
  MyClass cl;
  std::cout << cl.CurrentEnemy() << std::endl;

  std::cout << "After construction" << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  std::cout << "Resetting" << std::endl;
  cl.ResetEnumeration();

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;

  cl.Update();
  std::cout << cl.CurrentEnemy() << std::endl;
  // cl.Update();
  // cl.Update();
  // cl.Update();
  // cl.Update();
  // cl.Update();
}
