module;
#include <proxy/proxy_macros.h>

#include "global.h"
export module sheila:fixture;

import std;

import proxy.v4;

import :parameter;

namespace sheila {
#pragma region fixture
PRO_DEF_MEM_DISPATCH(SetUp, set_up);
PRO_DEF_MEM_DISPATCH(TearDown, tear_down);
PRO_DEF_MEM_DISPATCH(Execute, execute);

// clang-format off
struct Fixture final : pro::facade_builder
  ::add_convention<SetUp, void() noexcept>
  ::add_convention<TearDown, void() noexcept>
  ::add_convention<Execute, void()>
  ::build {};
// clang-format on

export struct SHEILA_API EmptyFixture {
  void set_up() noexcept;
  void tear_down() noexcept;
};

class CommonFixture : public EmptyFixture {
public:
  constexpr CommonFixture(void (*func)()) noexcept;

  void execute();

private:
  void (*func_)();
};
#pragma endregion fixture

#pragma region parameter fixture
PRO_DEF_MEM_DISPATCH(PreCase, pre_case);
PRO_DEF_MEM_DISPATCH(PostCase, post_case);

// clang-format off
template <class T>
struct ParameterFixture final : pro::facade_builder
  ::add_convention<SetUp, void() noexcept>
  ::add_convention<TearDown, void() noexcept>
  ::template add_convention<Execute, void(const T&)>
  ::template add_convention<PreCase, void(const T&) noexcept>
  ::template add_convention<PostCase, void(const T&) noexcept>
  ::build{};
// clang-format on

export template <class T>
class ParameterFixtureContainer {
public:
  ParameterFixtureContainer(pro::proxy<Parametric<T>> parameter,
      pro::proxy<ParameterFixture<T>> fixture) noexcept
      : parameter_(std::move(parameter)), fixture_(std::move(fixture)) {
  }

  void set_up() noexcept {
    fixture_->set_up();
  }

  void tear_down() noexcept {
    fixture_->tear_down();
  }

  void execute() {
    for_each(parameter_, [this](const T& val) {
      fixture_->pre_case(val);
      fixture_->execute(val);
      fixture_->post_case(val);
    });
  }

private:
  pro::proxy<Parametric<T>> parameter_;
  pro::proxy<ParameterFixture<T>> fixture_;
};

export template <class T>
class DefaultParameterFixture : public EmptyFixture {
public:
  using value_type = T;

  void pre_case(const T&) noexcept {
  }

  void post_case(const T&) noexcept {
  }
};
#pragma endregion parameter fixture

#pragma region type fixture
export template <class... Args>
struct TypeList {};

template <class F>
class TypeFixtureContainer {
public:
  TypeFixtureContainer(F fixture) noexcept : fixture_(std::move(fixture)) {
  }

  void set_up() noexcept {
    fixture_.set_up();
  }

  void tear_down() noexcept {
    fixture_.tear_down();
  }

  void execute() {
    for (auto&& type : type_args_) {
      std::invoke(std::get<0>(type), fixture_);
      std::invoke(std::get<1>(type), fixture_);
      std::invoke(std::get<2>(type), fixture_);
    }
  }

  template <class T, class... Args>
  void add_type() {
    if constexpr (sizeof...(Args) == 0) {
      auto arg = std::make_tuple(&F::template pre_case<T>,
          &F::template execute<T>, &F::template post_case<T>);
      type_args_.emplace_back(std::move(arg));
    } else {
      add_type<T>();
      add_type<Args...>();
    }
  }

  template <class... Args>
  void add_type(const TypeList<Args...>&) {
    add_type<Args...>();
  }

private:
  using Args =
      std::tuple<void (F::*)() noexcept, void (F::*)(), void (F::*)() noexcept>;

  std::vector<Args> type_args_;
  F fixture_;
};

export class DefaultTypeFixture : public EmptyFixture {
public:
  template <class T>
  void pre_case() noexcept {
  }

  template <class T>
  void post_case() noexcept {
  }
};
#pragma endregion type fixture

export template <class T, class... Args>
  requires(
      pro::proxiable_target<T, Fixture> && std::is_constructible_v<T, Args...>)
auto make_fixture(Args&&... args) noexcept -> pro::proxy<Fixture> {
  return pro::make_proxy<Fixture, T>(std::forward<Args>(args)...);
}

export template <class T, class... Args>
  requires(pro::proxiable_target<T, ParameterFixture<typename T::value_type>> &&
           std::is_constructible_v<T, Args...>)
auto make_parameter_fixture(
    pro::proxy<Parametric<typename T::value_type>> parameter,
    Args&&... args) noexcept -> pro::proxy<Fixture> {
  using value_type = typename T::value_type;
  using Container = ParameterFixtureContainer<value_type>;
  auto item = pro::make_proxy<ParameterFixture<value_type>, T>(
      std::forward<Args>(args)...);
  return pro::make_proxy<Fixture, Container>(
      std::move(parameter), std::move(item));
}

export template <class T, class Types, class... Args>
auto make_type_fixture(Args&&... args) noexcept -> pro::proxy<Fixture> {
  T item(std::forward<Args>(args)...);
  auto fixture = TypeFixtureContainer<T>(std::move(item));
  fixture.add_type(Types{});
  return pro::make_proxy<Fixture, TypeFixtureContainer<T>>(std::move(fixture));
}

}  // namespace sheila