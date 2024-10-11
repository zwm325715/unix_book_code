template<typename T1, typename T2>
//C++11:尾置返回类型，允许使用"调用参数(形参)"
auto max (T1 a, T2 b) -> decltype( b<a ? a:b ) {
  return  b < a ? a : b;
}
