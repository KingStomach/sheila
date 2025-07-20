#pragma once

#ifndef SHEILA_H
#define SHEILA_H

#define STRING_CAT_IMPL(str1, str2) str1##str2
#define STRING_CAT(str1, str2) STRING_CAT_IMPL(str1, str2)

#define UNIQUE_NAME(name) STRING_CAT(name##_, __LINE__)

#define TEST_REGISTER(func, ...)                  \
  static sheila::Register UNIQUE_NAME(register_)( \
      [] static { return func(__VA_ARGS__); })

#define DECLARE_TEST_FUNCTION(pre, name, ...)                                 \
  _Pragma("warning(push)") _Pragma("warning(disable : 4100)") pre static void \
  name(__VA_ARGS__) _Pragma("warning(pop)")

#define TEST_IMPL(name, tags, func)                   \
  DECLARE_TEST_FUNCTION(, func);                      \
  TEST_REGISTER(sheila::make_test, name, tags, func); \
  DECLARE_TEST_FUNCTION(, func)

#define TEST(name, tags) TEST_IMPL(name, tags, UNIQUE_NAME(test))

#define TEST_F_IMPL(class, name, tags, func)                         \
  DECLARE_TEST_FUNCTION(, func, class&);                             \
  TEST_REGISTER(sheila::make_test_fixture<class>, name, tags, func); \
  DECLARE_TEST_FUNCTION(, func, class& test)

#define TEST_F(class, name, tags) \
  TEST_F_IMPL(class, name, tags, UNIQUE_NAME(test))

#define TEST_P_IMPL(class, name, tags, func, parameter)                    \
  DECLARE_TEST_FUNCTION(, func, class&, typename class ::value_type&);     \
  TEST_REGISTER((sheila::make_parameter_test<class, decltype(parameter)>), \
                name, tags, parameter, func);                              \
  DECLARE_TEST_FUNCTION(, func, class& test, typename class ::value_type& val)

//
// #define DECLARE_PARAMETER_TEST(class, name, tags, func, parameter)          \
//  DECLARE_TEST_FUNCTION(, func, class&, typename class ::value_type&);      \
//  TEST_REGISTER(class, name, tags, sheila::rtti::make_generator(parameter), \
//                reinterpret_cast<void (*)(                                  \
//                    sheila::ParameterTest<typename class ::value_type>&,    \
//                    typename class ::value_type&)>(func));                  \
//  DECLARE_TEST_FUNCTION(, func, class& test, typename class ::value_type& val)
//
#define TEST_P(class, name, tags, parameters) \
  TEST_P_IMPL(class, name, tags, UNIQUE_NAME(test), parameters)

#endif  // SHEILA_H