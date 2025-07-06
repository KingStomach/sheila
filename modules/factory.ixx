export module sheila:factory;

import <memory>;
import <vector>;

import :test;

namespace sheila {
class Factory {
public:
  static Factory& instance();

  void add_test(std::unique_ptr<ITest>&& test);
  void run_all(int argc, char* argv[]) noexcept;

private:
  std::vector<std::unique_ptr<ITest>> tests_;
};
}  // namespace sheila