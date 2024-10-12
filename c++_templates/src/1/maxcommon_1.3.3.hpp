#include <type_traits>

//c++14
template<typename T1, typename T2>
std::common_type_t<T1,T2> max (T1 a, T2 b) {
  return  b < a ? a : b;
}

//c++11
template<typename T1, typename T2>
auto max2 (T1 a, T2 b) -> typename std::common_type<T1,T2>::type {
  return  b < a ? a : b;
}