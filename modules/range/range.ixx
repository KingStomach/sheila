export module sheila:range;

import std;

namespace sheila {
template <class T>
class IRange {
public:
  using value_type = T;

  template <class Self>
  decltype(auto) begin(this Self&& self) {
    return self.begin_impl();
  }

  template <class Self>
  decltype(auto) end(this Self&& self) {
    return self.end_impl();
  }
};
}  // namespace sheila