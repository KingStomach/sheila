module sheila;

import std;

namespace sheila::details {
std::string Logger::pass(std::string_view test) {
  return std::format("\033[0;32m[Test Pass]\033[0m: {}\n", test);
}

std::string Logger::fail(std::string_view test) {
  return std::format("\033[0;31m[Test Fail]\033[0m: {}\n", test);
}

std::string Logger::expect_fail(std::string_view matcher,
    std::string_view values, const std::source_location& loc) {
  return std::format(
      "\033[0;31m[Expect Fail]\033[0m at {} Line {}, Matcher: {}, Values: {}\n",
      loc.file_name(), loc.line(), matcher, values);
}

std::string Logger::unexpect_exception(const char* what) {
  return std::format(
      "\033[0;31m[Unexpect Exception]\033[0m: {}\n", what ? what : "");
}
}  // namespace sheila::details