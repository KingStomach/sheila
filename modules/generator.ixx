export module sheila:generator;

import <memory>;

namespace sheila {
template <class T>
class IGenerator {
public:
  template <class Self>
  decltype(auto) begin(this Self&& self) {
    return self.begin_impl();
  }

  template <class Self>
  decltype(auto) end(this Self&& self) {
    return self.end_impl();
  }
};

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
class Values final : public IGenerator<typename T::value_type> {
public:
  using value_type = T::value_type;
  using iterator = T::iterator;
  using value_type = T::value_type;

  template <class... Args>
  Values(Args&&... args) : container_(std::forward<Args>(args)...) {
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

  friend IGenerator<typename T::value_type>;

  T container_;
};

namespace rtti {
template <class T>
  requires(std::same_as<T, std::remove_reference_t<std::remove_volatile_t<T>>>)
class NOVTABLE IGenerator {
public:
  using value_type = T;
  constexpr virtual ~IGenerator() noexcept = default;

  virtual void begin() = 0;
  virtual void next() = 0;
  virtual bool end() = 0;
  virtual T* get() = 0;
};

template <class T>
using const_value_type_if =
    std::conditional_t<std::is_const_v<T>, const typename T::value_type,
                       typename T::value_type>;

template <class T>
  requires(
      std::same_as<T, std::remove_reference_t<std::remove_volatile_t<T>>> &&
      std::derived_from<T, sheila::IGenerator<const_value_type_if<T>>>)
class Generator : public IGenerator<const_value_type_if<T>> {
public:
  Generator(const T& container)
      : container_(container), iterator_(container_.begin()) {
  }

  virtual void begin() override {
    iterator_ = container_.begin();
  }

  virtual void next() override {
    ++iterator_;
  }

  virtual bool end() override {
    return iterator_ == container_.end();
  }

  virtual typename T::value_type* get() override {
    return std::addressof(*iterator_);
  }

private:
  T container_;
  typename T::iterator iterator_;
};

template <class T, class Fn>
void for_each(IGenerator<T>& gen, Fn&& fn) {
  for (gen.begin(); !gen.end(); gen.next()) {
    std::invoke(fn, *gen.get());
  }
}
}  // namespace rtti
}  // namespace sheila