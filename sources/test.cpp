module sheila;

namespace sheila {
// ITest
ITest::ITest(const char* name, const char*) : name_(name) {
}

void ITest::execute() {
  set_up();
  test_body();
  tear_down();
}

// Test
Test::Test(const char* name, const char* tags, void (*func)())
    : ITest(name, tags), func_(func) {
}

void Test::test_body() {
  func_();
}

// TestFixture
TestFixture::TestFixture(const char* name, const char* tags,
                         void (*func)(TestFixture&))
    : ITest(name, tags), func_(func) {
}

void TestFixture::test_body() {
  func_(*this);
}

}  // namespace sheila