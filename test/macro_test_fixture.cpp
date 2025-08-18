#include <assert.h>
#include <sheila.h>
import sheila;

namespace {
static bool set_up_has_call = false;
static bool tear_down_has_call = false;
static bool execute_has_call = false;
static bool empty_fixture_execute_has_call = false;

class Fixture {
public:
  void set_up() noexcept {
    set_up_has_call = true;
  }

  void tear_down() noexcept {
    tear_down_has_call = true;
  }

protected:
  int member_ = 1;
};

}  // namespace

using sheila::EmptyFixture;
TEST_F(EmptyFixture, "Macro.TestFixture.EmptyFixture", "") {
  empty_fixture_execute_has_call = true;
}

TEST_F(Fixture, "Macro.TestFixture", "") {
  execute_has_call = true;
  assert(member_ == 1);
}

int main(int argc, char* argv[]) {
  sheila::Manager::instance().init(argc, argv);
  if (sheila::Manager::instance().run_all_test())
    return 1;
  if (!set_up_has_call || !tear_down_has_call || !execute_has_call ||
      !empty_fixture_execute_has_call)
    return 1;
  return 0;
}