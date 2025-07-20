module;
#include "global.h"
export module sheila:factory;

import std;

import :test;

namespace sheila {
class Factory {
public:
  static Factory& instance();

  void add_test(std::unique_ptr<ITest>&& test);
  void run_all(int argc, char* argv[]) noexcept;

private:
  std::vector<std::unique_ptr<ITest>> tests_;
};

export SHEILA_API [[nodiscard]] int run_all_test(int argc,
                                                 char* argv[]) noexcept;

}  // namespace sheila