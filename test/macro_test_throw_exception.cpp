#include <sheila.h>
import std;
import sheila;

TEST("Macro.Test.ThrowException", "") {
  throw std::exception(ERROR_MESSAGE);
}

int main(int argc, char* argv[]) {
  sheila::Manager::instance().init(argc, argv);
  return sheila::Manager::instance().run_all_test() == 0;
}