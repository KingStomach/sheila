export module sheila:registration;

import <memory>;
import <source_location>;

import :test;

namespace sheila {
export class SHEILA_API Register {
public:
  Register(std::unique_ptr<ITest> (*func)(),
           const std::source_location& loc =
               std::source_location::current()) noexcept;
};
}  // namespace sheila