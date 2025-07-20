export module sheila:algorithm;

import std;

import :parameter;

namespace sheila {
template <class T, class Fn>
void for_each(IParameter<T>& gen, Fn&& fn) {
  for (gen.begin(); !gen.end(); gen.next()) {
    std::invoke(fn, *gen.get());
  }
}
}  // namespace sheila