// 从c++11开始，constexpr来启用在编译期使用代码计算某些数值的功能,对于很多模版来说，这是有意义的
template<typename T1, typename T2>
constexpr auto max (T1 a, T2 b) {
  return  b < a ? a : b;
}
