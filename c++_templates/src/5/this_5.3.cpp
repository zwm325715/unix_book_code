#include <iostream>
#include <ostream>

template<typename T>
class Base {
    public:
    void bar();
};

template<typename T>
void Base<T>::bar() {
    std::cout << " Base bar() " << std::endl;
}
void bar() {
    std::cout << "全局bar " << std::endl;
}

template<typename T>
class Derived : public Base<T> {
public:
    void foo() {
        std::cout << "Derived::foo() " << std::endl;
        //Cannot resolve symbol 'bar'
        //bar(); 错误
        this->bar();//可以
        Base<T>::bar();//可以
    }
};

int main(int argc, char *argv[]) {
    Derived<int> derived{};
    derived.foo();
}
