module;
#include "global.h"
export module sheila:manager;

import proxy.v4;

import :fixture;
import :logger;

namespace sheila {

export class Manager {
public:
  using Data = char[96];

  Manager(const Manager&) = delete;
  Manager(Manager&& test) = delete;
  Manager& operator=(const Manager&) = delete;
  Manager& operator=(Manager&& test) = delete;
  ~Manager() noexcept;
  SHEILA_API static Manager& instance();

  void add_test(
      const char* name, const char* tags, pro::proxy<Fixture> fixture);
  SHEILA_API void init(int argc, char* argv[]) noexcept;
  SHEILA_API [[nodiscard]] int run_all_test() noexcept;

  pro::proxy<Logger>& get_logger() noexcept;
  std::ostream& get_stream() noexcept;

private:
  Manager();

  Data data_{};
};

}  // namespace sheila