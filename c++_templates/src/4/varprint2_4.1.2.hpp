#include <iostream>

//非变参模版
template<typename T>
void print (T arg) {
    std::cout << arg << '\n';  // print passed argument
}

//变参模版
template<typename T, typename.../*类型是个变参:注意这里的省略号*/ Types>
void print (T firstArg, Types... args) {
    print(firstArg);  // call print() for the first argument
    //注意调用时也有省略号
    print(args...);   // call print() for remaining arguments
}
