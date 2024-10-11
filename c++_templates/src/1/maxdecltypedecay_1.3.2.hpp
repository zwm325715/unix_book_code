// std::decay<>在标准库<type_traits>中定义，参考附录D的D.4节
#include <type_traits>

template<typename T1, typename T2>
/*
  1.decay /dɪˈkeɪ/ n.衰退
  2.使用了类型特征std::decay<>,其返回结果类型为成员type.
      template<typename _Tp>
      class decay {
        typedef typename remove_reference<_Tp>::type __remove_type;
      public:
        typedef typename __decay_selector<__remove_type>::__type type;
      };
    可见type成员是一个类型，因此必须用typename来修饰这个表达式才能访问它(5.1节)    
*/
auto max (T1 a, T2 b) -> typename std::decay<decltype(true?a:b)>::type {
  return  b < a ? a : b;
}