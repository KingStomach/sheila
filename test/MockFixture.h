#ifndef MOCK_FIXTURE_H
#define MOCK_FIXTURE_H
#include <assert.h>

class MockFixture {
public:
  ~MockFixture() noexcept {
    assert(set_up_call_times_ == 1);
    assert(tear_down_times_ == 1);
  }

  void set_up() noexcept {
    set_up_call_times_++;
  }

  void tear_down() noexcept {
    tear_down_times_++;
  }

private:
  int set_up_call_times_ = 0;
  int tear_down_times_ = 0;
};

class MockParameterFixture : public {
public:
private:
};

#endif