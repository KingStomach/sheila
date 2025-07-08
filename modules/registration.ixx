export module sheila:registration;

import <utility>;

import :test;

namespace sheila {
export class SHEILA_API Register {
public:
  Register(ITest* test);
};

export template <class T, class... Args> requires(std::is_base_of_v<ITest, T>)
ITest* make_test(Args&&... args) noexcept {
  try {
    return new T(std::forward<Args>(args)...);
  }
  catch (...) {
    return nullptr;
  }
}
}  // namespace sheila