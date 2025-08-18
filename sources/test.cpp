module sheila;

namespace sheila {
namespace {
struct TestImpl {
  TestImpl(const char* name, const char*, pro::proxy<Fixture> fixture)
      : name(name), fixture(std::move(fixture)) {
  }

  std::string_view name;
  pro::proxy<Fixture> fixture;
};
static_assert(sizeof(TestImpl) == sizeof(Test::Data));

TestImpl* access(char* data) noexcept {
  return reinterpret_cast<TestImpl*>(data);
}

const TestImpl* access(const char* data) noexcept {
  return reinterpret_cast<const TestImpl*>(data);
}

#define ACCESS(IMPL) auto IMPL = access(this->data_);

}  // namespace

Test::Test(const char* name, const char* tags, pro::proxy<Fixture> fixture) {
  ACCESS(impl);
  std::construct_at(impl, name, tags, std::move(fixture));
}

Test::Test(Test&& test) noexcept {
  ACCESS(left);
  auto right = access(test.data_);
  left->name = std::move(right->name);
  left->fixture = std::move(right->fixture);
}

Test& Test::operator=(Test&& test) noexcept {
  ACCESS(left);
  auto right = access(test.data_);
  left->name = std::move(right->name);
  left->fixture = std::move(right->fixture);
  return *this;
}

Test::~Test() noexcept {
  ACCESS(impl);
  std::destroy_at(impl);
}

State Test::execute() noexcept {
  ACCESS(impl);
  auto& stream = Manager::instance().get_stream();
  auto& logger = Manager::instance().get_logger();

  impl->fixture->set_up();
  State state = State::Success;
  try {
    impl->fixture->execute();
  } catch (Error) {
  } catch (const std::exception& e) {
    stream << logger->unexpect_exception(e.what());
    state = State::Terminate;
  } catch (...) {
    stream << logger->unexpect_exception(nullptr);
    state = State::Terminate;
  }
  impl->fixture->tear_down();

  if (state == State::Success)
    stream << logger->pass(impl->name.data());
  else
    stream << logger->fail(impl->name.data());

  return state;
}

namespace {
void register_test(
    const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept {
  try {
    Manager::instance().add_test(name, tags, std::move(fixture));
  } catch (...) {
  }
}
}  // namespace

Register::Register(
    const char* name, const char* tags, void (*func)()) noexcept {
  register_test(name, tags, make_fixture<CommonFixture>(func));
}

Register::Register(
    const char* name, const char* tags, pro::proxy<Fixture> fixture) noexcept {
  register_test(name, tags, std::move(fixture));
}
}  // namespace sheila