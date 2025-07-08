export module sheila:test;

import <string_view>;

namespace sheila {
class NOVTABLE ITest {
public:
  constexpr ITest(const char* name, const char* tags);
  SHEILA_API constexpr virtual ~ITest() noexcept;

  SHEILA_API constexpr virtual void set_up();
  SHEILA_API constexpr virtual void tear_down();

  void execute();

private:
  virtual void test_body() = 0;
  std::string_view name_;
};

export class Test : public ITest {
public:
  SHEILA_API constexpr Test(const char* name, const char* tags,
    void (*func)(Test&));
private:
  SHEILA_API void test_body() override final;

  void (*func_)(Test&);
};
}  // namespace sheila