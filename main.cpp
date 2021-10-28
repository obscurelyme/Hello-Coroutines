#include <iostream>
#include <boost/coroutine2/all.hpp>
#include <functional>

template<typename T>
using coroutine = boost::coroutines2::coroutine<T>;


void myCoroutine(coroutine<void>::push_type &yield) {
    std::cout << "coroutine: Hello" << std::endl;
    yield();
    std::cout << "coroutine: World" << std::endl;
    yield();
    std::cout << "coroutine: Goodbye" << std::endl;
    yield();
    std::cout << "coroutine: Everyone" << std::endl;
}

int intCo(coroutine<int>::push_type &yield) {
    static int myInt = 0;
    while (true) {
        yield(++myInt);
    }
}

class MyClass {
    public:
    MyClass() {
        pull = new coroutine<int>::pull_type(std::bind(&MyClass::EnumerateEnemies, this, std::placeholders::_1));
    }
    ~MyClass() { delete pull; };

    void Update() {
        // if (_currentEnemySpawn < _maxEnemies) {
        //     (*pull)();
        // }
        try { 
            (*pull)();
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        
    }

    void EnumerateEnemies(coroutine<int>::push_type &yield) {
        // while (_currentEnemySpawn < _maxEnemies) {
        //     // spawn enemy...
        //     yield(_currentEnemySpawn++);
        // }
        yield(++_currentEnemySpawn);
    }

    void ResetEnumeration() {
        _currentEnemySpawn = 0;
    }

    int CurrentEnemy() const { return pull->get(); }

    private:
    coroutine<int>::pull_type* pull;
    int _currentEnemySpawn{0};
    int _maxEnemies{6};
};

int main(int, char**) {
    MyClass cl;
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
    cl.Update();
    std::cout << cl.CurrentEnemy() << std::endl;
    cl.Update();
    std::cout << cl.CurrentEnemy() << std::endl;
}
