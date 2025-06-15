#include <iostream>
#include <vector>
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

template<typename C,typename... Idx>
void printElems(C const& coll/*容器引用*/,Idx... idx/*类型模版参数包:索引*/) {
    //使用变参索引来访问传递的实参的相应元素
    print(coll[idx]...);//注意语法格式
}

template<std::size_t... Idx /*非类型模版参数包:直接固定类型*/, typename C>
void printElems2(C const& coll) {
    print(coll[Idx]...);
}

int main(int argc, char *argv[]) {
    std::vector<std::string> coll = {"good","times","say","bye"};
    //等价于print(coll[2],coll[0],coll[3])
    printElems(coll,2,0,3);
    std::cout << "---------------" << std::endl;
    printElems2<2,0,3 /*传索引*/>(coll);
}