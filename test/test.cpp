#include <sheila.h>
import sheila;

TEST("TEST", "") {
}

namespace {
class Fixture {
public:
  void set_up() noexcept {
  }

  void tear_down() noexcept {
  }
};
}  // namespace

TEST_F(Fixture, "TEST_F", "") {
}

namespace {
using MyParameterFixture = sheila::DefaultParameterFixture<int>;
}

TEST_P(MyParameterFixture, "TEST_P", "", sheila::values({1, 2, 3})) {
}

namespace {
class ParameterFixture {
public:
  using value_type = int;

  void set_up() noexcept {
  }
  void tear_down() noexcept {
  }

  void pre_case(const int&) noexcept {
  }

  void post_case(const int&) noexcept {
  }
};
}  // namespace

TEST_P(ParameterFixture, "TEST_P", "", sheila::values({1, 2, 3})) {
}

namespace {
using MyTypeFixture = sheila::DefaultTypeFixture;
}

TEST_T(MyTypeFixture, "TEST_T", "", TYPES(int, short, float)) {
}