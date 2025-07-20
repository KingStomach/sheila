module;
#include "global.h"
export module sheila:registration;

import std;

import :range;
import :parameter;
import :test;
import :test_fixture;
import :parameter_test;

namespace sheila {
export class SHEILA_API Register {
public:
  Register(std::unique_ptr<ITest> (*func)(),
           const std::source_location& loc =
               std::source_location::current()) noexcept;
};

export inline auto make_test(const char* name, const char* tags, void (*func)())
    -> std::unique_ptr<ITest> {
  return std::make_unique<Test>(name, tags, func);
}

export template <class T>
  requires(std::derived_from<T, TestFixture>)
inline auto make_test_fixture(const char* name, const char* tags,
                              void (*func)(T&)) -> std::unique_ptr<ITest> {
  return std::make_unique<T>(
      name, tags, reinterpret_cast<void (*)(sheila::TestFixture&)>(func));
}

export template <class T, class P>
  requires(std::derived_from<T, ParameterTest<typename T::value_type>> &&
           std::derived_from<P, IRange<typename T::value_type>>)
inline auto make_parameter_test(const char* name, const char* tags,
                                P&& parameter,
                                void (*func)(T&, typename T::value_type&))
    -> std::unique_ptr<ITest> {
  return std::make_unique<T>(
      name, tags, std::make_unique<Parameter<P>>(std::forward<P>(parameter)),
      reinterpret_cast<void (*)(sheila::ParameterTest<typename T::value_type>&,
                                typename T::value_type&)>(func));
}
}  // namespace sheila