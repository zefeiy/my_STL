#ifndef MYSTL_TYPE_TRAITS_H_
#define MYSTL_TYPE_TRAITS_H_


// 这个头文件用于提取类型信息
// use standard header for type_traits
#include <type_traits>

namespace mystl {

//helper struct

template <class T, T v>
struct m_integral_constant{
  static constexpr T value = v;
};



}








#endif