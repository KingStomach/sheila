module sheila;

import std;

namespace sheila {
namespace {
struct TestImpl {
  TestImpl(std::ostream& out) noexcept : out(out) {
  }

  std::ostream& out;
};
static_assert(sizeof(TestImpl) == sizeof(Test::Data));

#define ACCESS(IMPL) auto IMPL = details::impl_cast<TestImpl>(this->data_);
}  // namespace

Test::Test(std::ostream& out) noexcept {
  ACCESS(impl);
  std::construct_at(impl, out);
}

Test::~Test() noexcept {
  ACCESS(impl);
  std::destroy_at(impl);
}

void Test::expect_impl(std::string_view matcher, std::string_view values,
    const std::source_location& loc) {
  throw details::Assert{
      .message = details::Logger::expect_fail(matcher, values, loc)};
}
}  // namespace sheila