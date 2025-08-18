// module sheila;
//
// namespace sheila {
//
//// Factory
// Factory& Factory::instance() {
//   static Factory impl;
//   return impl;
// }
//
// void Factory::add_test(Test&& test) {
//   tests_.emplace_back(std::move(test));
// }
//
// void Factory::run_all(int, char*[]) noexcept {
//   for (auto&& test : tests_) {
//     test.execute();
//   }
// }
//
//// Register
// namespace {
// void register_test(
//     const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept
//     {
//   try {
//     Factory::instance().add_test(Test(name, tags, std::move(fixture)));
//   } catch (...) {
//   }
// }
// }  // namespace
//
// Register::Register(
//     const char* name, const char* tags, void (*func)()) noexcept {
//   register_test(name, tags, make_fixture<CommonFixture>(func));
// }
//
// Register::Register(
//     const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept
//     {
//   register_test(name, tags, std::move(fixture));
// }
//
//// Other
// int run_all_test(int argc, char* argv[]) noexcept {
//   Factory::instance().run_all(argc, argv);
//   return 0;
// }
//
// constexpr const char* ErrorCategory::name() const noexcept {
//   return "sheila::Error";
// }
//
// std::string ErrorCategory::message(int) const {
//   return "";
// }
//
// const std::error_category& error_category() noexcept {
//   static ErrorCategory category;
//   return category;
// }
//
// std::error_code make_error_code(Error error) noexcept {
//   return std::error_code(static_cast<int>(error), error_category());
// }
// }  // namespace sheila