#include <iostream>

template<int Val, typename T>
T addValue (T x) {
  return x + Val;
}

//指定 "模版参数类型(T)" 从 "前面的参数(非类型参数Val)" 推导而来
template<auto Val,typename T=decltype(Val)>
T foo();

//确保 "传递的值(非类型参数Val)的类型" 和 "传递的类型(模版参数T)" 一致
template<typename T, T Val = T{}/*默认0值*/>
T bar();