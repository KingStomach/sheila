export module sheila:test;

import <string_view>;

namespace sheila {
class NOVTABLE ITest {
public:
  constexpr ITest(const char* name, const char* tags);
  constexpr virtual ~ITest() noexcept;

  constexpr virtual void set_up();
  constexpr virtual void tear_down();
  constexpr virtual void pre_case();
  constexpr virtual void post_case();

  void execute();

private:
  virtual void execute_impl() = 0;
  std::string_view name_;
};

class Test : public ITest {
public:
  constexpr Test(const char* name, const char* tags,
                 void (*func)(void)) noexcept;

private:
  void execute_impl() override;

  void (*func_)(void);
};
}  // namespace sheila