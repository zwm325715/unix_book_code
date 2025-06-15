#include <array>
#include <complex.h>
#include <iostream>
#include <tuple>
#include <variant>
void print() {}
//变参模版
template<typename T, typename... Types>
void print (T firstArg, Types... args) {
    std::cout << "接收到的参数值:" << firstArg << std::endl;
    //C++11开始提供
    if (sizeof...(args) > 0) {
        print(args...);
    }
}

//第25章
// template <typename... Elements>
// class Tuple;

//第26章
// template <typename... Types>
// class Variant;

//索引列表的类型
template <std::size_t...>
struct Indices {};

template <typename T,std::size_t... Idx>
void printByIdx(T t, Indices<Idx...>) {
    print(std::get<Idx>(t)...);
}

int main(int argc, char *argv[]) {
    //t可以保存整型,字符串或字符类型
    std::tuple<int,std::string,char> t;

    //v可以保存整型,字符串或字符类型
    std::variant<int,std::string,char> v;

    //使用方式1
    std::array<std::string,5> arr = {"Hello","my","new","!","World"};
    printByIdx(arr,Indices<0,4,3>());
    //使用方式2:这也是迈向元编程的第一步
    auto t2 = std::make_tuple(12,"monkeys",2.0);
    printByIdx(t2,Indices<0,1,2>());
}
