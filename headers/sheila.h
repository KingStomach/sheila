#pragma once

#ifndef SHEILA_H
#define SHEILA_H

#define STRING_CAT_IMPL(str1, str2) str1##str2
#define STRING_CAT(str1, str2) STRING_CAT_IMPL(str1, str2)

#define UNIQUE_NAME(name) STRING_CAT(name##_, __LINE__)

#define TEST_REGISTER(name, tags, func, class)\
static sheila::Register UNIQUE_NAME(register_)(sheila::make_test<class>(name, tags, func))

#define DECLARE_FUNCTION_TEST(name, tags, func, class) \
static void func(class&); \
TEST_REGISTER(name, tags, reinterpret_cast<void (*)(sheila::Test&)>(func), class); \
void func(class& test)

#define TEST(name, tags) DECLARE_FUNCTION_TEST(name, tags, UNIQUE_NAME(test), sheila::Test)
#define TEST_F(class, name, tags) DECLARE_FUNCTION_TEST(name, tags, UNIQUE_NAME(test), class)

#endif  // SHEILA_H