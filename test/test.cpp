#include <sheila.h>
import sheila;

TEST("TEST", "") {
}

class MyTest_F : public sheila::TestFixture {
public:
  using sheila::TestFixture::TestFixture;

  void set_up() noexcept override {
  }
  void tear_down() noexcept override {
  }
};

TEST_F(MyTest_F, "TEST_F", "") {
}

class MyTest_P : public sheila::ParameterTest<int> {
public:
  using sheila::ParameterTest<int>::ParameterTest;

  void set_up() noexcept override {
  }
  void tear_down() noexcept override {
  }

  void pre_case(int&) noexcept override {
  }

  void post_case(int&) noexcept override {
  }
};

TEST_P(MyTest_P, "TEST_P", "", sheila::value<int>({1, 2, 3})) {
}