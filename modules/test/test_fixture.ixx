module;
#include "global.h"
export module sheila:test_fixture;

import :test;

namespace sheila {
export class TestFixture : public ITest {
public:
  SHEILA_API TestFixture(const char* name, const char* tags,
                         void (*func)(TestFixture&));

private:
  SHEILA_API void test_body() override;

  void (*func_)(TestFixture&);
};
}  // namespace sheila