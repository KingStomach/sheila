#pragma once

#ifndef SHEILA_H
#define SHEILA_H

#define TEST_NAME(name) test_##name

#define TEST(name, tags)                                           \
  static void TEST_NAME(name)();                                   \
  static sheila::Register test_##name##_register(#name, #tags,     \
                                                 TEST_NAME(name)); \
  void TEST_NAME(name)()

#endif  // SHEILA_H