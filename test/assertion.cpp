#include <sheila.h>
import sheila;
import std;

class AssertionTest : public sheila::Test {
public:
  using sheila::Test::Test;

  void test_boolean() {
    expect(true);
  }
};
RegisterTest(&AssertionTest::test_boolean, "");

SHEILA_MAIN_FUNCTION