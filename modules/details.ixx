module;
#include <proxy/proxy_macros.h>
export module sheila:details;

import std;

import proxy.v4;

namespace sheila::details {
struct Uncopyable {
  constexpr Uncopyable() noexcept = default;
  Uncopyable(const Uncopyable&) = delete;
  Uncopyable& operator=(const Uncopyable&) = delete;
};

template <class T>
T* impl_cast(char* data) noexcept {
  return reinterpret_cast<T*>(data);
}

template <class T>
const T* impl_cast(const char* data) noexcept {
  return reinterpret_cast<const T*>(data);
}

// template <class Fn>
//   requires(std::is_invocable_v<Fn, std::string_view>)
// void spilt_tags(const char* tags, const Fn& fn) noexcept(
//     std::is_nothrow_invocable_v<Fn, std::string_view>) {
//   std::string_view str(tags);
//   size_t i = 0, j = 0, k = str.size();
//   do {
//     i = str.find_first_of('[', i);
//     j = str.find_first_of(']', i + 1);
//     fn(str.substr(i + 1, j - i));
//   } while (j == std::string_view::npos || j == k);
// }

template <class T, class... Args>
class Fixture : Uncopyable {
public:
  Fixture(void (T::*func)(Args...),
      std::vector<std::tuple<std::remove_cvref_t<Args>...>> parameters)
      : func_(func), parameters_(std::move(parameters)) {
  }

  void test(std::ostream& out) {
    test_impl(out, std::make_index_sequence<sizeof...(Args)>{});
  }

private:
  template <size_t... Indices>
  void test_impl(std::ostream& out, std::index_sequence<Indices...>) {
    T test_(out);
    for (auto&& parameter : parameters_) {
      std::invoke(func_, test_, std::get<Indices>(parameter)...);
    }
  }

  void (T::*func_)(Args...);
  std::vector<std::tuple<std::remove_cvref_t<Args>...>> parameters_;
};

template <class T>
class Fixture<T> : Uncopyable {
public:
  Fixture(void (T::*func)()) : func_(func) {
  }

  void test(std::ostream& out) {
    T test_(out);
    std::invoke(func_, test_);
  }

private:
  void (T::*func_)();
};

PRO_DEF_MEM_DISPATCH(Test, test);

// clang-format off
struct Testable final : pro::facade_builder
  ::add_convention<Test, void(std::ostream&)>
  ::build {};
// clang-format on

struct Logger {
  static std::string pass(std::string_view test);
  static std::string fail(std::string_view test);
  static std::string expect_fail(std::string_view matcher,
      std::string_view values, const std::source_location& loc);
  static std::string unexpect_exception(const char* what);
};

struct Assert {
  std::string message;
};

template <class T, class... Args>
void try_format_impl(std::string& result, const T& value, const Args&... args) {
  if constexpr (std::formattable<T, char>)
    std::format_to(std::back_inserter(result), "{}", value);
  else
    result += "Unknown value";

  if constexpr (sizeof...(Args) > 0) {
    result.push_back(' ');
    try_format_impl(result, args...);
  }
}

template <class... Args>
std::string try_format(const Args&... args) {
  std::string result;
  try_format_impl(args...);
  return result;
}
}  // namespace sheila::details
