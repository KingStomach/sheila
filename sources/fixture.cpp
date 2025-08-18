module sheila;

namespace sheila {
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
}  // namespace sheila