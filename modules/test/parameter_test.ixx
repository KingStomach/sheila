export module sheila:parameter_test;

import std;

import :algorithm;
import :parameter;
import :test;
import :test_fixture;

namespace sheila {
export template <class T>
  requires(std::same_as<T, std::remove_cv_t<T>>)
class ParameterTest : public ITest {
public:
  using value_type = T;

  ParameterTest(const char* name, const char* tags,
                std::unique_ptr<IParameter<T>> gen,
                void (*func)(ParameterTest&, T&))
      : ITest(name, tags), generator_(std::move(gen)), func_(func) {
  }

  virtual void pre_case(T&) noexcept {
  }
  virtual void post_case(T&) noexcept {
  }

private:
  void test_body() override final {
    for_each(*generator_, [this](auto&& element) {
      pre_case(element);
      func_(*this, element);
      post_case(element);
    });
  }

  std::unique_ptr<IParameter<T>> generator_;
  void (*func_)(ParameterTest&, T&);
};
}  // namespace sheila