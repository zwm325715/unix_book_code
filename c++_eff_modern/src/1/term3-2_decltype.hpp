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