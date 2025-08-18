#include <sheila.h>
import sheila;

TEST("Macro.Test.ThrowNotException", "") {
  throw 1;
}

int main(int argc, char* argv[]) {
  sheila::Manager::instance().init(argc, argv);
  return sheila::Manager::instance().run_all_test() == 0;
}