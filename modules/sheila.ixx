export module sheila;

import :factory;
export import :registration;
export import :test;

namespace sheila {
export SHEILA_API int run_all_test(int argc, char* argv[]) noexcept;
}