#include "global.h"
export module sheila;

export import :details;

import std;

import proxy.v4;

namespace sheila {
export struct Equal : std::equal_to<void> {
  constexpr static std::string_view name = "Equal";
};

export struct True {
  constexpr static std::string_view name = "True";
};

class Test : details::Uncopyable {
public:
  using Data = char[8];

  Test(std::ostream& os) noexcept;
  ~Test() noexcept;

  template <class Arg>
  void expect(const std::source_location& loc, const Arg& arg) {
    expect(loc, True{}, arg);
  }
  template <class Matcher, class... Args>
  void expect(const std::source_location& loc, const Matcher& matcher,
      const Args&... args) {
    if (std::invoke(matcher, args...))
      return;

    expect_impl(Matcher::name, details::try_format(args...), loc);
  }

private:
  [[noreturn]] void expect_impl(std::string_view matcher,
      std::string_view values, const std::source_location& loc);
  Data data_;
};

class Manager : details::Uncopyable {
public:
  using Data = char[32];

  Manager();
  ~Manager() noexcept;

  static Manager& instance();
  void add_test(
      const char* name, const char* tags, pro::proxy<details::Testable> test);

  int run_all_test(int argc, char* argv[]) noexcept;

private:
  Data data_;
};

export template <class T, class... Args>
  requires(sizeof...(Args) > 0)
int register_test(void (T::*func)(Args&&...), const char* name,
    const char* tags,
    std::vector<std::tuple<std::remove_cvref_t<Args>...>> parameters) {
  using Fixture = details::Fixture<T, Args...>;
  auto fixture = pro::make_proxy<Fixture>(func, std::move(parameters));
  Manager::instance().add_test(name, tags, std::move(fixture));
}

export template <class T>
int register_test(void (T::*func)(), const char* name, const char* tags) {
  using Fixture = details::Fixture<T>;
  auto fixture = pro::make_proxy<Fixture>(func);
  Manager::instance().add_test(name, tags, std::move(fixture));
}
}  // namespace sheila
