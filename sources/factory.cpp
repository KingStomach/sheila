module sheila;

namespace sheila {
Factory& Factory::instance() {
  static Factory impl;
  return impl;
}

void Factory::add_test(std::unique_ptr<ITest>&& test) {
  tests_.emplace_back(std::move(test));
}

void Factory::run_all(int argc, char* argv[]) noexcept {
  for (auto&& test : tests_) {
    test->execute();
  }
}

int run_all_test(int argc, char* argv[]) noexcept {
  Factory::instance().run_all(argc, argv);
  return 0;
}

}  // namespace sheila