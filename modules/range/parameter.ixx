module;
#include "global.h"
export module sheila:parameter;

import std;

import :range;

namespace sheila {
namespace {
template <class T>
using const_value_type_if =
    std::conditional_t<std::is_const_v<T>, const typename T::value_type,
                       typename T::value_type>;
}

template <class T>
  requires(std::same_as<T, std::remove_reference_t<std::remove_volatile_t<T>>>)
class NOVTABLE IParameter {
public:
  using value_type = T;
  constexpr virtual ~IParameter() noexcept = default;

  virtual void begin() = 0;
  virtual void next() = 0;
  virtual bool end() = 0;
  virtual T* get() = 0;
};

template <class T>
  requires(
      std::same_as<T, std::remove_reference_t<std::remove_volatile_t<T>>> &&
      std::derived_from<T, sheila::IRange<const_value_type_if<T>>>)
class Parameter : public IParameter<const_value_type_if<T>> {
public:
  Parameter(const T& container)
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

}  // namespace sheila