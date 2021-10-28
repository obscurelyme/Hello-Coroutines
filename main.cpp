#include <iostream>
#include <boost/coroutine2/all.hpp>

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

int main(int, char**) {
    coroutine<void>::pull_type resume{myCoroutine};
    std::cout << "[main]: ....... " << std::endl; //flush here
    resume();
    std::cout << "[main]: here at NETWAYS! :)" << std::endl;
    std::cout << "[main]: here at NETWAYS! :)" << std::endl;
    std::cout << "[main]: here at NETWAYS! :)" << std::endl;
    std::cout << "[main]: here at NETWAYS! :)" << std::endl;
    std::cout << "[main]: here at NETWAYS! :)" << std::endl;
    resume();
    resume();
}
