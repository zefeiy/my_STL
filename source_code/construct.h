
#ifndef MYSTL_CONSTRUCT_H_
#define MYSTL_CONSTRUCT_H_

// 这个头文件包含两个函数 construct，destroy
// construct : 负责对象的构造
// destroy   : 负责对象的析构

#include<new>

namespace mystl {

// construct 构造对象
template <class Ty>
void construct(Ty* ptr) {
    ::operator new ((void*)ptr) Ty();
}

template <class Ty1, class Ty2>
void construct(Ty1* ptr, const Ty2& value) {
    ::operator new ((void*)ptr) Ty1(value);
}

//这里不是很理解，得寻找完美转发理解
template <class Ty, class... Args>
void construct(Ty* ptr, Args&&... args)
{
  ::new ((void*)ptr) Ty(mystl::forward<Args>(args)...);
}

//析构对象   ，根据不同类型来选择析构
template <class Ty>
void destroy_one(Ty*, std::true_type) {}

template <class Ty>
void destroy_one(Ty* pointer, std::false_type){
  if (pointer != nullptr){
    pointer->~Ty();
  }
}


template <class ForwardIter>
void destroy_cat(ForwardIter , ForwardIter , std::true_type) {}


template <class ForwardIter>
void destroy_cat(ForwardIter first, ForwardIter last, std::false_type){
  for (; first != last; ++first)
    destroy(&*first);
}


template <class Ty>
void destroy(Ty* pointer){
  destroy_one(pointer, std::is_trivially_destructible<Ty>{});
}


template <class ForwardIter>
void destroy(ForwardIter first, ForwardIter last){
  destroy_cat(first, last, std::is_trivially_destructible<
              typename iterator_traits<ForwardIter>::value_type>{});
}





}




#endif