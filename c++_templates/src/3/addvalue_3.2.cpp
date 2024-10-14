#include "addvalue_3.2.hpp"
#include <algorithm>
int main() {
    //1.非类型的函数模版参数
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> result(nums.size());
    /*
    1.可以将函数模版用作参数
        例如c++标准库,可以传递"该函数模版的实例化对象"来为集合中的每个元素增加一个值
    2.std::transform 函数是 C++ 标准库中的一个通用算法。
        transform函数的作用是将输入范围内的每个元素通过一元操作函数进行处理，
        并将处理后的结果存储在输出范围内。 
    3.注意 ：
        必须为addValue<>的模版参数T指定实参为int类型，因为类型推导只适用于立即调用，
        而std::transform()又需要一个完整的类型来推导其第4个参数的类型.       
    */
    std::transform(nums.begin(),nums.end(),//源集合的起点和终点
                    result.begin(),//目标集合的起点
                    addValue<5,int>/*执行的操作函数*/);

    //2.参数推导
    foo<1,int>();//OK

    bar<int,"1">(); //编译错误：类型不一致
    bar<int,1>(); //OK
    
    
}