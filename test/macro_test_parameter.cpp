#include <assert.h>
#include <sheila.h>
import std;
import sheila;

namespace {
static std::vector<int> parameters{1, 2, 3};
static int fixture_1_call_times = 0;
static int fixture_2_call_times = 0;
static bool set_up_has_call = false;
static bool tear_down_has_call = false;
static int pre_case_call_times = 0;
static int post_case_call_times = 0;

using Fixture_1 = sheila::DefaultParameterFixture<int>;

class Fixture_2 {
public:
  using value_type = int;

  void set_up() noexcept {
    set_up_has_call = true;
  }

  void tear_down() noexcept {
    tear_down_has_call = true;
  }

  void pre_case(const int& val) noexcept {
    assert(parameters[pre_case_call_times] == val);
    pre_case_call_times++;
  }

  void post_case(const int& val) noexcept {
    assert(parameters[post_case_call_times] == val);
    post_case_call_times++;
  }

protected:
  int member_ = 0;
};
}  // namespace

TEST_P(Fixture_1, "Macro.TestParameter.DefaultFixture", "", parameters) {
  assert(parameters[fixture_1_call_times] == val);
  fixture_1_call_times++;
}

TEST_P(Fixture_2, "Macro.TestParameter.Fixture", "", parameters) {
  assert(parameters[fixture_2_call_times] == val);
  fixture_2_call_times++;
  assert(member_ == 0);
}

int main(int argc, char* argv[]) {
  sheila::Manager::instance().init(argc, argv);
  if (sheila::Manager::instance().run_all_test())
    return 1;
  assert(fixture_1_call_times == parameters.size());
  assert(fixture_2_call_times == parameters.size());
  assert(pre_case_call_times == parameters.size());
  assert(post_case_call_times == parameters.size());
  return 0;
}