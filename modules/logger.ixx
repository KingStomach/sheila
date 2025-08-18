module;
#include <proxy/proxy_macros.h>

#include "global.h"
export module sheila:logger;

import std;
import proxy.v4;

namespace sheila {
enum class Error {
  Expect,
  Assert,
};

PRO_DEF_MEM_DISPATCH(Pass, pass);
PRO_DEF_MEM_DISPATCH(Fail, fail);
PRO_DEF_MEM_DISPATCH(Expect, expect_fail);
PRO_DEF_MEM_DISPATCH(Assert, assert_fail);
PRO_DEF_MEM_DISPATCH(Exception, unexpect_exception);

// clang-format off
struct Logger final : pro::facade_builder
  ::add_convention<Pass, std::string(const char*)>
  ::add_convention<Fail, std::string(const char*)>
  ::add_convention<Expect, std::string(const char*, const std::source_location&)>
  ::add_convention<Assert, std::string(const char*, const std::source_location&)>
  ::add_convention<Exception, std::string(const char*)>
  ::build {};
// clang-format on

SHEILA_TEST_EXPORT struct TerminalLogger {
  SHEILA_TEST_API std::string pass(const char* test);
  SHEILA_TEST_API std::string fail(const char* test);
  SHEILA_TEST_API std::string expect_fail(
      const char* message, const std::source_location& loc);
  SHEILA_TEST_API std::string assert_fail(
      const char* message, const std::source_location& loc);
  SHEILA_TEST_API std::string unexpect_exception(const char* what);
};
}  // namespace sheila