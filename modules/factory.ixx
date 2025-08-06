module;
#include "global.h"
export module sheila:factory;

import std;

import proxy.v4;

import :fixture;

namespace sheila {
class Test {
public:
  Test(const char* name, const char* tags, pro::proxy<Fixture> fixture);

  void execute();

private:
  std::string_view name_;
  pro::proxy<Fixture> fixture_;
};

class Factory {
public:
  static Factory& instance();

  void add_test(Test&& test);
  void run_all(int argc, char* argv[]) noexcept;

private:
  std::vector<Test> tests_;
};

export SHEILA_API [[nodiscard]] int run_all_test(
    int argc, char* argv[]) noexcept;

export struct SHEILA_API Register {
  Register(const char* name, const char* tags, void (*func)()) noexcept;
  Register(
      const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept;
};

}  // namespace sheila