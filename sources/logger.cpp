module sheila;

namespace sheila {
std::string TerminalLogger::pass(const char* test) {
  return std::format("\033[0;32m[Test Pass]\033[0m: {}\n", test);
}

std::string TerminalLogger::fail(const char* test) {
  return std::format("\033[0;31m[Test Fail]\033[0m: {}\n", test);
}

std::string TerminalLogger::expect_fail(
    const char* message, const std::source_location& loc) {
  return std::format("\033[0;31m[Expect Fail]\033[0m: {}, at {} Line {}\n",
      message, loc.file_name(), loc.line());
}

std::string TerminalLogger::assert_fail(
    const char* message, const std::source_location& loc) {
  return std::format("\033[0;31m[Assert Fail]\033[0m: {}, at {} Line {}\n",
      message, loc.file_name(), loc.line());
}

std::string TerminalLogger::unexpect_exception(const char* what) {
  return std::format(
      "\033[0;31m[Unexpect Exception]\033[0m: {}\n", what ? what : "");
}
}  // namespace sheila