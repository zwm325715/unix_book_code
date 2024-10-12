#include <type_traits>
// 使用std::common_type<>类型特征来指定返回类型的默认值
template<typename T1, typename T2,
         typename RT = std::common_type_t<T1,T2>>
RT max (T1 a, T2 b) {
  return  b < a ? a : b;
}
