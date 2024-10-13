#include <vector>
#include <iostream>

template<typename T>
class Stack {
    private:
        std::vector<T> elems;
    public:
        Stack() = default;
        
        Stack(const T elem)
            /*注意：
                当不使用大括号{}赋值，也就是elems(elem)，
                此时vector容器不是初始元素为5的容器，而是初始5个元素的空间大小
            */
            :elems({std::move(elem)}) {
            std::cout << "构造函数推导~!" <<std::endl;
        }
};