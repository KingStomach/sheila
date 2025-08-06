module;
#include <proxy/proxy_macros.h>

#include "global.h"
export module sheila:parameter;

import std;

import proxy.v4;

namespace sheila {
PRO_DEF_MEM_DISPATCH(Begin, begin);
PRO_DEF_MEM_DISPATCH(End, end);
PRO_DEF_MEM_DISPATCH(Next, next);
PRO_DEF_MEM_DISPATCH(Get, get);

// clang-format off
template <class T>
struct Parametric final : pro::facade_builder
  ::add_convention<Begin, void() noexcept>
  ::add_convention<End, bool() noexcept>
  ::add_convention<Next, void() noexcept>
  ::template add_convention<Get, const T&() noexcept>
  ::build {};
// clang-format on

template <class T>
  requires(std::same_as<T, std::remove_cvref_t<T>> &&
           requires(T t) {
             typename T::value_type;
             typename T::iterator;
             { t.begin() } -> std::same_as<typename T::iterator>;
             { t.end() } -> std::same_as<typename T::iterator>;
           } && std::input_iterator<typename T::iterator>)
class Parameter {
public:
  using value_type = T::value_type;

  Parameter(T container) noexcept
      : container_(std::move(container)), iterator_(container_.begin()) {
  }

  void begin() noexcept {
    iterator_ = container_.begin();
  }

  bool end() const noexcept {
    return iterator_ == container_.end();
  }

  void next() noexcept {
    ++iterator_;
  }

  const T::value_type& get() noexcept {
    return *iterator_;
  }

private:
  T container_;
  T::iterator iterator_;
};

export template <class T, template <class...> class Container = std::vector>
decltype(auto) values(std::initializer_list<T> list) {
  return Container<T>(list);
}

export template <class Container>
decltype(auto) make_parameter(Container&& container) noexcept {
  using Pure = std::remove_cvref_t<Container>;
  return pro::make_proxy<Parametric<typename Pure::value_type>,
      Parameter<Pure>>(std::forward<Container>(container));
}

SHEILA_TEST_EXPORT template <class T, class Fn>
  requires(std::invocable<Fn, T>)
void for_each(pro::proxy<Parametric<T>>& gen, Fn&& fn) {
  for (gen->begin(); !gen->end(); gen->next()) {
    std::invoke(fn, gen->get());
  }
}
}  // namespace sheila