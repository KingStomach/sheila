#pragma once

#ifndef SHEILA_H
#define SHEILA_H

#define STRING_CAT_IMPL(str1, str2) str1##str2
#define STRING_CAT(str1, str2) STRING_CAT_IMPL(str1, str2)

#define UNIQUE_NAME(name) STRING_CAT(name##_, __LINE__)

#define TEST(name, tags)                         \
  static void UNIQUE_NAME(test)();               \
  static sheila::Register UNIQUE_NAME(register)( \
      name, tags, UNIQUE_NAME(test));            \
  void UNIQUE_NAME(test)()

#define TEST_F(fixture, name, tags, ...)                                    \
  struct UNIQUE_NAME(Fixture) : public fixture {                            \
    using fixture::fixture;                                                 \
    void execute();                                                         \
  };                                                                        \
  static sheila::Register UNIQUE_NAME(register)(                            \
      name, tags, sheila::make_fixture<UNIQUE_NAME(Fixture)>(__VA_ARGS__)); \
  void UNIQUE_NAME(Fixture)::execute()

#define TEST_P(fixture, name, tags, parameter, ...)                       \
  struct UNIQUE_NAME(Fixture) : public fixture {                          \
    using fixture::fixture;                                               \
    void execute(const fixture::value_type&);                             \
  };                                                                      \
  static sheila::Register UNIQUE_NAME(register)(name, tags,               \
      sheila::make_parameter_fixture<UNIQUE_NAME(Fixture)>(               \
          sheila::make_parameter(parameter) __VA_OPT__(, ) __VA_ARGS__)); \
  _Pragma("warning(push)") _Pragma("warning(disable : 4100)") void        \
  UNIQUE_NAME(Fixture)::execute(const fixture::value_type&)               \
      _Pragma("warning(pop)")

#define TYPES(...) sheila::TypeList<__VA_ARGS__>

#define TEST_T(fixture, name, tags, types, ...)                              \
  struct UNIQUE_NAME(Fixture) : public fixture {                             \
    using fixture::fixture;                                                  \
    template <class T>                                                       \
    void execute();                                                          \
  };                                                                         \
  static sheila::Register UNIQUE_NAME(register)(                             \
      name, tags, sheila::make_type_fixture<UNIQUE_NAME(Fixture), types>()); \
  template <class T>                                                         \
  void UNIQUE_NAME(Fixture)::execute()

#endif  // SHEILA_H