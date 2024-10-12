#include <type_traits>

template<typename T1, 
         typename T2,
         //decay:确保不返回引用类型
         typename RT = 
            typename std::decay<decltype(true ? T1() : T2())>::type //c++11
            // std::decay_t<decltype(true ? T1() : T2())>   c++14
        >
RT max (T1 a, T2 b) {
  return  b < a ? a : b;
}
