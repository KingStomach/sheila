#include <sheila.h>
import sheila;

static bool has_been_call = 0;

TEST("Macro.Test", "") {
  has_been_call = 1;
}

int main(int argc, char* argv[]) {
  sheila::Manager::instance().init(argc, argv);
  if (sheila::Manager::instance().run_all_test() || !has_been_call)
    return 1;
  return 0;
}