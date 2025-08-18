module;
#include "global.h"
export module sheila:test;

import proxy.v4;

import :fixture;

namespace sheila {
enum class State {
  Success,
  Continue,
  Terminate,
};

class Test {
public:
  using Data = char[40];

  Test(const char* name, const char* tags, pro::proxy<Fixture> fixture);
  Test(const Test&) = delete;
  Test(Test&& test) noexcept;
  Test& operator=(const Test&) = delete;
  Test& operator=(Test&& test) noexcept;
  ~Test() noexcept;

  State execute() noexcept;

private:
  Data data_{};
};

export struct SHEILA_API Register {
  Register(const char* name, const char* tags, void (*func)()) noexcept;
  Register(
      const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept;
};
}  // namespace sheila