module sheila;

namespace sheila {
constexpr ITest::ITest(const char* name, const char* tags) : name_(name) {
}

constexpr ITest::~ITest() noexcept = default;

constexpr void ITest::set_up() {
}

constexpr void ITest::tear_down() {
}

constexpr void ITest::pre_case() {
}

constexpr void ITest::post_case() {
}

void ITest::execute() {
  set_up();
  execute_impl();
  tear_down();
}

constexpr Test::Test(const char* name, const char* tags,
                     void (*func)(void)) noexcept
    : ITest(name, tags), func_(func) {
}

void Test::execute_impl() {
  pre_case();
  func_();
  post_case();
}
}  // namespace sheila