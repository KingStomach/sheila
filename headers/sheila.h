#pragma once

#ifndef SHEILA_H
#define SHEILA_H

#define STRING_CAT_IMPL(str1, str2) str1##str2
#define STRING_CAT(str1, str2) STRING_CAT_IMPL(str1, str2)

#define UNIQUE_NAME(name) STRING_CAT(name##_, __LINE__)

#define TEST_REGISTER(class, ...)                    \
  static sheila::Register UNIQUE_NAME(register_)(    \
      [] -> std::unique_ptr<sheila::ITest> {         \
        return std::make_unique<class>(__VA_ARGS__); \
      })

#define DECLARE_TEST_FUNCTION(pre, name, ...) pre static void name(__VA_ARGS__)

#define DECLARE_FUNCTION_TEST(class, name, tags, func)            \
  DECLARE_TEST_FUNCTION(, func, class&);                          \
  TEST_REGISTER(class, name, tags,                                \
                reinterpret_cast<void (*)(sheila::Test&)>(func)); \
  DECLARE_TEST_FUNCTION(, func, class& test)

#define TEST(name, tags) \
  DECLARE_FUNCTION_TEST(sheila::Test, name, tags, UNIQUE_NAME(test))
#define TEST_F(class, name, tags) \
  DECLARE_FUNCTION_TEST(class, name, tags, UNIQUE_NAME(test))

#define DECLARE_PARAMETER_TEST(class, name, tags, func, parameter)          \
  DECLARE_TEST_FUNCTION(, func, class&, typename class ::value_type&);      \
  TEST_REGISTER(class, name, tags, sheila::rtti::make_generator(parameter), \
                reinterpret_cast<void (*)(                                  \
                    sheila::ParameterTest<typename class ::value_type>&,    \
                    typename class ::value_type&)>(func));                  \
  DECLARE_TEST_FUNCTION(, func, class& test, typename class ::value_type& val)

#define TEST_P(class, name, tags, parameters) \
  DECLARE_PARAMETER_TEST(class, name, tags, UNIQUE_NAME(test), parameters)

#endif  // SHEILA_H