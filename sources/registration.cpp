module sheila;

namespace sheila {
Register::Register(std::unique_ptr<ITest> (*func)(),
    const std::source_location& loc) noexcept {
  try {
    Factory::instance().add_test(func());
  } catch (...) {
  }
}
}  // namespace sheila