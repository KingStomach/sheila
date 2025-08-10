module;
#include "global.h"
export module sheila:error;

import std;

namespace sheila {
enum class Error {
  Success,
  Fail,
  Expect,
  Assert,
  Exception,
};

class ErrorCategory final : public std::error_category {
public:
  constexpr const char* name() const noexcept override;

  [[nodiscard]] std::string message(int error) const override;
};

[[nodiscard]] const std::error_category& error_category() noexcept;
[[nodiscard]] std::error_code make_error_code(Error error) noexcept;
}  // namespace sheila

namespace std {
template <>
struct is_error_code_enum<sheila::Error> : public true_type {};

}  // namespace std