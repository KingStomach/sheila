module sheila;

import <memory>;

import :factory;
import :test;

namespace sheila {
Register::Register(ITest* test) {
  Factory::instance().add_test(std::unique_ptr<ITest>(test));
}
}  // namespace sheila