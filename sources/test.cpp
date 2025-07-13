module sheila;

namespace sheila {
constexpr ITest::ITest(const char* name, const char* tags) : name_(name) {
}

constexpr void ITest::set_up() {
}

constexpr void ITest::tear_down() {
}

void ITest::execute() {
  set_up();
  test_body();
  tear_down();
}

constexpr Test::Test(const char* name, const char* tags, void (*func)(Test&))
    : ITest(name, tags), func_(func) {
}

void Test::test_body() {
  func_(*this);
}
}  // namespace sheila