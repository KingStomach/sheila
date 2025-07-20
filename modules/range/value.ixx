export module sheila:value;

import std;

import :range;

namespace sheila {
template <class T>
  requires(
      std::same_as<T, std::remove_cv_t<T>> &&
      requires(T t) {
        typename T::value_type;
        typename T::iterator;
        typename T::const_iterator;
        { t.begin() } -> std::same_as<typename T::iterator>;
        { t.end() } -> std::same_as<typename T::iterator>;
      } &&
      requires(const T t) {
        { t.begin() } -> std::same_as<typename T::const_iterator>;
        { t.end() } -> std::same_as<typename T::const_iterator>;
      } && std::input_iterator<typename T::iterator> &&
      std::input_iterator<typename T::const_iterator>)
class Value final : public IRange<typename T::value_type> {
public:
  using iterator = T::iterator;

  template <class... Args>
  Value(Args&&... args) : container_(std::forward<Args>(args)...) {
  }

private:
  template <class Self>
  decltype(auto) begin_impl(this Self&& self) {
    return self.container_.begin();
  }

  template <class Self>
  decltype(auto) end_impl(this Self&& self) {
    return self.container_.end();
  }

  friend IRange<typename T::value_type>;

  T container_;
};

export template <class T,
                 template <class... Args> class Container = std::vector,
                 class... Args>
[[nodiscard]] Value<Container<T>> value(Args&&... args) {
  return Value<Container<T>>(std::forward<Args>(args)...);
}

export template <class T,
                 template <class... Args> class Container = std::vector>
[[nodiscard]] Value<Container<T>> value(const std::initializer_list<T>& list) {
  return Value<Container<T>>(list);
}
}  // namespace sheila