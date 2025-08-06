import sheila;
#include <sheila.h>

namespace {
struct Fixture_1 : sheila::EmptyFixture {
  void execute() {
  }
};

struct Fixture_2 {
  void set_up() noexcept {
  }

  void tear_down() noexcept {
  }

  void execute() {
  }
};

struct Fixture_3 {
  Fixture_3(int) noexcept {
  }

  void set_up() noexcept {
  }

  void tear_down() noexcept {
  }

  void execute() {
  }
};

class ParameterFixture_1 : public sheila::DefaultParameterFixture<int> {
public:
  void execute(const int&) {
  }
};

class ParameterFixture_2 {
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

  void execute(const int&) {
  }
};

class TypeFixture_1 : public sheila::DefaultTypeFixture {
public:
  template <class T>
  void execute() {
  }
};

class TypeFixture_2 {
public:
  void set_up() noexcept {
  }

  void tear_down() noexcept {
  }

  template <class T>
  void pre_case() noexcept {
  }

  template <class T>
  void post_case() noexcept {
  }

  template <class T>
  void execute() {
  }
};
}  // namespace

TEST("make_fixture", "") {
  sheila::make_fixture<Fixture_1>();
  sheila::make_fixture<Fixture_2>();
  sheila::make_fixture<Fixture_3>(1);
}

namespace {
template <class T, class... Args>
void make_parameter_fixture_test(Args&&... args) noexcept {
  auto parameter = sheila::make_parameter(std::vector<int>{1, 2, 3});
  sheila::make_parameter_fixture<T>(
      std::move(parameter), std::forward<Args>(args)...);
}
}  // namespace

TEST("make_parameter_fixture", "") {
  make_parameter_fixture_test<ParameterFixture_1>();
  make_parameter_fixture_test<ParameterFixture_2>();
}

TEST("make_type_fixture", "") {
  sheila::make_type_fixture<TypeFixture_1, sheila::TypeList<int, short>>();
  sheila::make_type_fixture<TypeFixture_2, sheila::TypeList<int, short>>();
}
