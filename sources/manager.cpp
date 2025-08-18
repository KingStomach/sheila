module sheila;

import proxy.v4;

namespace sheila {
namespace {
struct ManagerImpl {
  ManagerImpl()
      : logger(pro::make_proxy<Logger, TerminalLogger>()), out(&std::cout) {
  }

  std::vector<Test> tests;
  std::vector<std::string_view> error_messages;
  pro::proxy<Logger> logger;
  std::ostream* out;
};
static_assert(sizeof(ManagerImpl) == sizeof(Manager::Data));

ManagerImpl* access(char* data) noexcept {
  return reinterpret_cast<ManagerImpl*>(data);
}

const ManagerImpl* access(const char* data) noexcept {
  return reinterpret_cast<const ManagerImpl*>(data);
}

#define ACCESS(IMPL) auto IMPL = access(this->data_);
}  // namespace

Manager::Manager() {
  ACCESS(impl);
  std::construct_at(impl);
}

Manager::~Manager() noexcept {
  ACCESS(impl);
  std::destroy_at(impl);
}

Manager& Manager::instance() {
  static Manager impl;
  return impl;
}

void Manager::add_test(
    const char* name, const char* tags, pro::proxy<Fixture> fixture) {
  ACCESS(impl);
  impl->tests.emplace_back(name, tags, std::move(fixture));
}

static std::map<std::string_view, void (*)(ManagerImpl&)> no_args_callback = {};
static std::map<std::string_view, void (*)(ManagerImpl&, std::string_view)>
    single_args_callback = {};

void Manager::init(int argc, char* argv[]) noexcept {
  ACCESS(impl);

  for (int i = 1; i < argc; i++) {
    std::string_view arg(argv[i]);
    if (arg.starts_with('-')) {
      auto iter = no_args_callback.find(arg);
      if (iter != no_args_callback.end()) {
        iter->second(*impl);
      }
    } else if (arg.starts_with("--")) {
      auto iter = single_args_callback.find(arg);
      if (iter != single_args_callback.end()) {
        iter->second(*impl, arg.substr(arg.find_first_of('=')));
      }
    }
  }
}

int Manager::run_all_test() noexcept {
  ACCESS(impl);
  int success_count = 0;
  bool error = false;

  for (auto&& test : impl->tests) {
    State state = test.execute();

    switch (state) {
      case State::Success:
        success_count++;
        break;
      case State::Continue:
        error = true;
        break;
      case State::Terminate:
        return true;
    }
  }

  return error;
}

pro::proxy<Logger>& Manager::get_logger() noexcept {
  ACCESS(impl);
  return impl->logger;
}
std::ostream& Manager::get_stream() noexcept {
  ACCESS(impl);
  return *impl->out;
}

}  // namespace sheila