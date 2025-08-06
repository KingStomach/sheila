module sheila;

namespace sheila {
#pragma region fixture
// EmptyFixture
void EmptyFixture::set_up() noexcept {
}

void EmptyFixture::tear_down() noexcept {
}

// CommonFixture
constexpr CommonFixture::CommonFixture(void (*func)()) noexcept : func_(func) {
}

void CommonFixture::execute() {
  func_();
}
#pragma endregion

// Test
Test::Test(const char* name, const char*, pro::proxy<Fixture> fixture)
    : name_(name), fixture_(std::move(fixture)) {
}

void Test::execute() {
  fixture_->set_up();
  try {
    fixture_->execute();
  } catch (...) {
  }
  fixture_->tear_down();
}

// Factory
Factory& Factory::instance() {
  static Factory impl;
  return impl;
}

void Factory::add_test(Test&& test) {
  tests_.emplace_back(std::move(test));
}

void Factory::run_all(int, char*[]) noexcept {
  for (auto&& test : tests_) {
    test.execute();
  }
}

// Register
namespace {
void register_test(
    const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept {
  try {
    Factory::instance().add_test(Test(name, tags, std::move(fixture)));
  } catch (...) {
  }
}
}  // namespace

Register::Register(
    const char* name, const char* tags, void (*func)()) noexcept {
  register_test(name, tags, make_fixture<CommonFixture>(func));
}

Register::Register(
    const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept {
  register_test(name, tags, std::move(fixture));
}

// Other
int run_all_test(int argc, char* argv[]) noexcept {
  Factory::instance().run_all(argc, argv);
  return 0;
}
}  // namespace sheila