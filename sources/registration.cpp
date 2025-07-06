module sheila;

import <memory>;

import :factory;
import :test;

namespace sheila {
Register::Register(const char* name, const char* tags, void (*func_)(void)) {
  Factory::instance().add_test(std::make_unique<Test>(name, tags, func_));
}
}  // namespace sheila