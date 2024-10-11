template<typename T1, typename T2>
//c++14:仅使用auto，通过函数体中的返回语句推导返回值
auto max (T1 a, T2 b) {
  return  b < a ? a : b;
}
