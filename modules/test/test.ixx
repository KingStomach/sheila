module;
#include "global.h"
export module sheila:test;

import std;

namespace sheila {
class NOVTABLE ITest {
public:
  SHEILA_API ITest(const char* name, const char* tags);
  constexpr virtual ~ITest() noexcept = default;

  ITest(const ITest&) = delete;
  ITest(ITest&&) = delete;
  ITest& operator=(const ITest&) = delete;
  ITest&& operator=(ITest&&) = delete;

  void execute();

private:
  SHEILA_API virtual void set_up() noexcept {
  }
  SHEILA_API virtual void tear_down() noexcept {
  }
  virtual void test_body() = 0;

  std::string_view name_;
};

export class Test : public ITest {
public:
  SHEILA_API Test(const char* name, const char* tags, void (*func)());

private:
  void test_body() override final;

  void (*func_)();
};
}  // namespace sheila