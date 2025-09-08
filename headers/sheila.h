#pragma once

#ifndef SHEILA_H
#define SHEILA_H

#define STRCAT_2(a, b) a##b
#define STRCAT(a, b) STRCAT_2(a, b)

#define RegisterTest(func, tags, ...) \
  auto STRCAT(_, __LINE__) =          \
      sheila::register_test(func, #func, tags __VA_OPT__(, ) __VA_ARGS__)

#define SHEILA_MAIN_FUNCTION                                     \
  int main(int argc, char* argv[]) {                             \
    return sheila::Manager::instance().run_all_test(argc, argv); \
  }

#define expect(...) _expect(std::source_location::current(), __VA_ARGS__)

#endif  // SHEILA_H