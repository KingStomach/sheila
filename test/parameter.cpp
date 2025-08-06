import std;
import sheila;
#include <sheila.h>

TEST("Values", "") {
  sheila::values({1, 2, 3});
  sheila::values<int, std::set>({1, 2, 3});
  sheila::values<short>({1, 2, 3});
}

TEST("Parameter", "") {
  auto p1 = sheila::make_parameter(sheila::values({1, 2, 3}));
  auto p2 = sheila::make_parameter(std::set<int>{1, 2, 3});

  sheila::for_each(p1, [](const int&) {});
  sheila::for_each(p2, [](const int&) {});
}