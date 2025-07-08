import sheila;

TEST("TEST", "") {}
  
class MyTest : public sheila::Test{
public:
  using sheila::Test::Test;

  void set_up() override{}
  void tear_down() override {}
};

TEST_F(MyTest, "TEST_F", ""){}