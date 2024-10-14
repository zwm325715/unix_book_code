#include <iostream>
//1
const int i = 0;
//2
class Widget{};
bool f(const Widget& w);

//3
struct Point {
    int x,y;
};

//4
template<typename T>
class my_vector {
    public:
        T& operator[](std::size_t index);
};