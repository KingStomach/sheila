#pragma once

#ifndef SHEILA_H
#define SHEILA_H

#define RegisterTest(func, tags, ...) \
  auto _##__LINE__ =                  \
      sheila::register_test(func, #func, tags, __VA_OPT__(, ) __VA_ARGS__);

#define SHEILA_MAIN_FUNCTION                           \
  int main(int argc, char* argv[]) {                   \
    sheila::Manager::instance().init(argc, argv);      \
    return sheila::Manager::instance().run_all_test(); \
  }

#endif  // SHEILA_H