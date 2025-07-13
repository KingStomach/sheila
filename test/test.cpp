import sheila;
import <vector>;

TEST("TEST", "") {
}

class MyTest_F : public sheila::Test {
public:
  using sheila::Test::Test;

  void set_up() override {
  }
  void tear_down() override {
  }
};

TEST_F(MyTest_F, "TEST_F", "") {
}

class MyTest_P : public sheila::ParameterTest<int> {
public:
  using sheila::ParameterTest<int>::ParameterTest;

  void pre_case(int&) override {
  }

  void post_case(int&) override {
  }
};

TEST_P(MyTest_P, "TEST_P", "", sheila::values<int>({1, 2, 3})) {
}