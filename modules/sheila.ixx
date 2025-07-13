export module sheila;

import <vector>;

export import <memory>;

import :factory;
import :generator;

export import :registration;
export import :test;

namespace sheila {
export SHEILA_API [[nodiscard]] int run_all_test(int argc,
                                                 char* argv[]) noexcept;

export template <class T,
                 template <class... Args> class Container = std::vector,
                 class... Args>
[[nodiscard]] Values<Container<T>> values(Args&&... args) {
  return Values<Container<T>>(std::forward<Args>(args)...);
}

export template <class T,
                 template <class... Args> class Container = std::vector>
[[nodiscard]] Values<Container<T>> values(
    const std::initializer_list<T>& list) {
  return Values<Container<T>>(list);
}

namespace rtti {
export template <class Container>
[[nodiscard]] decltype(auto) make_generator(Container&& c) {
  return std::make_unique<Generator<std::remove_cvref_t<Container>>>(c);
}
}  // namespace rtti
}  // namespace sheila