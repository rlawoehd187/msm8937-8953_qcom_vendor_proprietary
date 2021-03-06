// --~--~--~--~----~--~--~--~----~--~--~--~----~--~--~--~----~--~--~--~--
// Copyright 2013-2015 Qualcomm Technologies, Inc.
// All rights reserved.
// Confidential and Proprietary – Qualcomm Technologies, Inc.
// --~--~--~--~----~--~--~--~----~--~--~--~----~--~--~--~----~--~--~--~--
#pragma once

#if defined(MARE_HAVE_QTI_HEXAGON)

#include <mare/internal/task/hexagonkernel.hh>

MARE_GCC_IGNORE_BEGIN("-Weffc++");

namespace mare {

template<typename Fn>
class hexagon_kernel;

template<typename ...Args>
class hexagon_kernel<int(*)(Args...)> : public ::mare::internal::hexagon_kernel<Args...> {

  using parent = ::mare::internal::hexagon_kernel<Args...>;

  template<typename X, typename Y>
  friend struct ::mare::internal::task_factory_dispatch;

  template<typename X, typename Y>
  friend struct ::mare::internal::task_factory;

public:

  using size_type = typename parent::size_type;
  using return_type = typename parent::return_type;
  using args_tuple = typename parent::args_tuple;

  using fn_type = typename parent::dsp_code_type;

  using collapsed_task_type = typename parent::collapsed_task_type;
  using non_collapsed_task_type = typename parent::non_collapsed_task_type;

  static MARE_CONSTEXPR_CONST size_type arity = parent::arity;

  static_assert( std::is_same<return_type, int>::value == true, "Functions for "
      "Hexagon kernels must return int");

  explicit hexagon_kernel(fn_type const& fn) :
    parent(fn) {
  }

  explicit hexagon_kernel(fn_type&& fn) :
    parent(std::forward<fn_type>(fn)) {
  }

  hexagon_kernel(hexagon_kernel const& other) :
    parent(other) {
  }

  hexagon_kernel(hexagon_kernel && other) :
    parent(std::move(other)) {
  }

  hexagon_kernel& operator=(hexagon_kernel const& other) {
    return static_cast<hexagon_kernel&>(parent::operator=(other));
  }

  hexagon_kernel& operator=(hexagon_kernel&& other) {
    return static_cast<hexagon_kernel&>(parent::operator=(std::move(other)));
  }

  ~hexagon_kernel() { }
};

template<typename ...Args>
MARE_CONSTEXPR_CONST typename hexagon_kernel<int(*)(Args...)>::size_type hexagon_kernel<int(*)(Args...)>::arity;

template <typename... Args>
mare::hexagon_kernel<int(*)(Args...)> create_hexagon_kernel(int(*fn)(Args...)) {
  return mare::hexagon_kernel<int(*)(Args...)>(fn);
}

};
MARE_GCC_IGNORE_END("-Weffc++");

#endif
