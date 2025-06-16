#include <iostream>

// print elements of an STL container 输出STL容器中的元素
template<typename T>
void printcoll (T const& coll/*是T类型的STL容器*/) {
    // iterator to iterate over coll 迭代coll的迭代器
    typename T::const_iterator/*容器的迭代器类型*/ pos;
    // end position 结束位置
    typename T::const_iterator end(coll.end());

    for (pos=coll.begin(); pos!=end; ++pos) {
        std::cout << *pos << ' ';
    }

    std::cout << '\n';
}

