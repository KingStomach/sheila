export module sheila:test;

import <memory>;
import <string_view>;

import :generator;

namespace sheila {
export class NOVTABLE ITest {
public:
  SHEILA_API constexpr ITest(const char* name, const char* tags);
  constexpr virtual ~ITest() noexcept = default;

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

export template <class T>
  requires(std::same_as<T, std::remove_cv_t<T>>)
class ParameterTest : public ITest {
public:
  using value_type = T;

  ParameterTest(const char* name, const char* tags,
                std::unique_ptr<rtti::IGenerator<T>>&& gen,
                void (*func)(ParameterTest&, T&))
      : ITest(name, tags), generator_(std::move(gen)), func_(func) {
  }

  virtual void pre_case(T&) {
  }
  virtual void post_case(T&) {
  }

private:
  void test_body() override {
    rtti::for_each(*generator_, [this](auto&& element) {
      pre_case(element);
      func_(*this, element);
      post_case(element);
    });
  }

  std::unique_ptr<rtti::IGenerator<T>> generator_;
  void (*func_)(ParameterTest&, T&);
};
}  // namespace sheila