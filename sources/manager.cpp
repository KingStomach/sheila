module sheila;

import std;

import proxy.v4;

namespace sheila {
namespace {
struct TestData {
  std::string_view original_name;
  std::string_view original_tags;
  pro::proxy<details::Testable> test;

  const std::string& name() {
    if (name_.has_value())
      return *name_;

    std::regex pattern1("&.+::.+");
    std::regex pattern2("static_cast<\\(.+\\)(\\(.+\\))>\\(&(.+::.+)\\)");
    if (std::regex_match(
            original_name.begin(), original_name.end(), pattern1)) {
      name_.emplace(original_name.substr(1));
    } else if (std::cmatch result;
        std::regex_match(original_name.data(), result, pattern2)) {
      name_.emplace(result.str(2) + result.str(1));
    } else
      name_.emplace("Unknown");

    return *name_;
  }

  std::optional<std::string> name_;
  std::optional<std::set<std::string_view>> tags_;
};

struct ManagerImpl {
  std::vector<TestData> cases;
};
static_assert(sizeof(ManagerImpl) == sizeof(Manager::Data));

#define ACCESS(IMPL) auto IMPL = details::impl_cast<ManagerImpl>(this->data_);

std::map<std::string_view, void (*)(ManagerImpl&)> no_args_callback = {};
std::map<std::string_view, void (*)(ManagerImpl&, std::string_view)>
    single_args_callback = {};
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
    const char* name, const char* tags, pro::proxy<details::Testable> test) {
  ACCESS(impl);
  impl->cases.emplace_back(TestData{
      .original_name = name, .original_tags = tags, .test = std::move(test)});
}

int Manager::run_all_test(int, char*[]) noexcept {
  ACCESS(impl);

  std::vector<int> orders(impl->cases.size());
  std::ranges::iota(orders, 0);
  std::ranges::shuffle(orders, std::mt19937(std::random_device()()));

  int success_count = 0;
  for (int index : orders) {
    bool success = true;
    auto& data = impl->cases[index];
    try {
      data.test->test(std::cout);
    } catch (const details::Assert& assert) {
      success = false;
      std::cout << assert.message;
    } catch (const std::exception& e) {
      success = false;
      std::cout << details::Logger::unexpect_exception(e.what());
    } catch (...) {
      success = false;
      std::cout << details::Logger::unexpect_exception(nullptr);
    }

    auto& name = data.name();
    if (success) {
      success_count++;
      std::cout << details::Logger::pass(name.c_str());
    } else
      std::cout << details::Logger::fail(name.c_str());
  }

  return success_count != impl->cases.size();
}
}  // namespace sheila