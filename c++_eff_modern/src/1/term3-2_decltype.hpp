#include <iostream>

//1.c++11能运作，但是需要改进
template<typename Container,typename Index>
auto authAndAccess1(Container& c,Index i) -> decltype(c[i]) {
    return c[i];
}

//2.c++14, 不甚(程度不高)正确
template<typename Container,typename Index>
auto authAndAccess2(Container& c,Index i) {
    return c[i];//返回值类型通过c[i]推导出来
}

/*
    3.c++14, 能运行，但仍需改进
      decltype(auto):
        auto指定了欲实施推导的类型，而推导过程中采用的是decltype规则
        也就意味着本函数的返回值和c[i]的类型一致了(不会在auto推导过程中省略&了)
*/
template<typename Container,typename Index>
decltype(auto) authAndAccess3(Container& c,Index i) {
    return c[i];
}

//C++14最终版:对容器使用万能引用
template<typename Container,typename Index>
decltype(auto) authAndAccess4(Container&& c,Index i) {
    //使用完美转发
    return std::forward<Container>(c) [i];
}

//C++11最终版:对容器使用万能引用
template<typename Container,typename Index>
auto authAndAccess5(Container&& c,Index i) ->decltype(std::forward<Container>(c)[i]){
    //使用完美转发
    return std::forward<Container>(c) [i];
}

//5.C++14，decltype(auto)用在变量声明
class Widget {};

