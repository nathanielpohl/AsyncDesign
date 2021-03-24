// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch6.h"

#include <chrono>
#include <iostream>
#include <mutex>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh6::FPInCppCh6(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh6::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
// Template class for lazy evaluation of functions
template <typename F>
class lazy_eval {
 private:
  F computation_;
  // Use an optinal so that the result of computation_ doesn't have to be
  // default constructable.
  mutable std::optional<decltype(computation_())> cache_;
  mutable std::once_flag value_flag;

 public:
  lazy_eval(F computation) : computation_(computation) {}

  lazy_eval(lazy_eval&& other) : computation_(std::move(other.computation_)) {}

  // Allow for implicit casting of a lazy_eval type to the return type of our
  // computation function.
  operator decltype(computation_())() const {
    // Call once is used here so that this class is thread safe.
    std::call_once(value_flag, [this] { cache_ = computation_(); });
    return *cache_;
  }
};

// Convience funciton. Allows for calls that don't specify the template type.
template <typename F>
inline lazy_eval<F> make_lazy_eval(F&& computation) {
  return lazy_eval<F>(std::forward<F>(computation));
}

//=============================================================================
// Template function for memoizied function results
template <typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...)) {
  std::unordered_map<std::tuple<Args...>, Result> cache;

  // Return a lambda with the function(f) and the cache value bound. The lambda
  // also needs to be mutable so that cache can be updated.
  return [f, cache](Args... args) mutable -> Result {
    const auto args_tuple = std::make_tuple(args...);
    const auto cached = cache.find(args_tuple);

    if (cache == cache.end()) {
      auto result = f(args...);
      cache[args_tuple] = result;
      return result;
    } else {
      return cached->second;
    }
  };
}

//=============================================================================

//=============================================================================
}  // namespace

//=============================================================================
int FPInCppCh6::Execute() {
  std::cout << "###################################################"
            << std::endl;
  std::cout << "####         Scratch pad from Chapter 6        ####"
            << std::endl;
  std::cout << "###################################################"
            << std::endl;

  {  // Lazy_eval tests.
    std::cout << "Lazy eval tests" << std::endl;
    std::cout << "Create foo, of type lazy_eval<(int) -> int>. This function "
                 "should not print \"lazy eval\"."
              << std::endl;
    auto foo = make_lazy_eval([]() {
      std::cout << "lazy eval" << std::endl;
      return 5;
    });
    std::cout << std::endl;

    std::cout << "Assign foo to an int. This should cast lazy_eval<> to an int "
                 "implicitly, and we should see \"lazy eval\" printed."
              << std::endl
              << std::endl;

    int bar = foo;
    std::cout << std::endl;

    std::cout << "Now assign foo to another int. Here we should not see \"lazy "
                 "eval\" printed, since the return value is cached."
              << std::endl;

    int baz = foo;
    std::cout << std::endl;

    // Get rid of unused variable errors.
    bar = baz;
    baz = bar;

    std::cout << std::endl;
  }

  std::cout << std::endl;

  return 0;
}
}  // namespace fpic_modules
