// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch6.h"

#include <glog/logging.h>

#include <iostream>
#include <map>
#include <mutex>
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
// Template class for lazy evaluation of functions.
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
// Template function for memoizied function results.
template <typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...)) {
  // This is not a thread safe impelementation of make_memoized.
  std::map<std::tuple<Args...>, Result> cache_;

  // Return a lambda with the function(f) and the cache value bound. The lambda
  // also needs to be mutable so that cache can be updated.
  return [f, cache_](Args... args) mutable -> Result {
    const auto args_tuple = std::make_tuple(args...);
    const auto cached = cache_.find(args_tuple);

    if (cached == cache_.end()) {
      auto result = f(args...);
      cache_[args_tuple] = result;
      return result;
    } else {
      return cached->second;
    }
  };
}

//=============================================================================
// Template classes for recusively memoizing. These helper will capture the
// intermediary recursive results. IE memoize_helper() -> func() ->
// memeoize_helper() -> func()...
class null_param {};

template <class Sig, class F>
class memoize_helper;

template <class Result, class... Args, class F>
class memoize_helper<Result(Args...), F> {
 private:
  using function_type = F;
  using arg_tuple_type = std::tuple<std::decay_t<Args>...>;

  function_type computation_;
  mutable std::map<arg_tuple_type, Result> cache_;
  mutable std::recursive_mutex cache_mutex_;

 public:
  template <typename Function>
  memoize_helper(Function&& computation, null_param)
      : computation_(computation) {}
  memoize_helper(const memoize_helper& other)
      : computation_(other.computation_) {}

  template <class... InnerArgs>
  Result operator()(InnerArgs&&... args) const {
    // This lock serializes all the access to the cache.
    std::lock_guard<std::recursive_mutex> lock{cache_mutex_};

    const auto args_tuple = std::make_tuple(args...);
    const auto cached = cache_.find(args_tuple);

    if (cached == cache_.end()) {
      auto&& result = computation_(*this, std::forward<InnerArgs>(args)...);
      cache_[args_tuple] = result;
      return result;
    } else {
      return cached->second;
    }
  }
};

template <class Sig, class F>
memoize_helper<Sig, std::decay_t<F>> make_memoized_r(F&& f) {
  // Initializer list construction of a memoize_helper class.
  return {std::forward<F>(f), null_param()};
}

// Functions specific to memoizing the Levenshtein distance. Note that lambda
// will call it's self through a refence to the memoize_helper class, which will
// be passed to it as the first argument LevenshteinDistance.
auto LevenshteinDistanceMemo =
    make_memoized_r<int(int, int, std::string, std::string)>(
        [](auto& LevenshteinDistance, int m, int n, std::string a,
           std::string b) {
          // This is expenseive to copy the string so much, but thats the best
          // way that I can come up with haveing a unique signature for all the
          // entries in the cache of memoize_hleper.
          auto a_temp = a;
          auto b_temp = b;
          a_temp.pop_back();
          b_temp.pop_back();

          int result =
              m == 0   ? n
              : n == 0 ? m
                       : std::min({LevenshteinDistance(m - 1, n, a_temp, b) + 1,
                                   LevenshteinDistance(m, n - 1, a, b_temp) + 1,
                                   LevenshteinDistance(m - 1, n - 1, a_temp,
                                                       b_temp) +
                                       int(a[m - 1] != b[n - 1])});
          LOG(INFO) << "The difference between a: \"" << a << "\" and b: \""
                    << b << "\" was: " << result;
          return result;
        });

//=============================================================================
// Template class for lazy string concatination.
template <typename... Strings>
class lazy_string_concat_helper;

template <typename LastString, typename... Strings>
class lazy_string_concat_helper<LastString, Strings...> {
 private:
  // A copy is made of the data instead of a reference, since we could have
  // refences change underneath us unexpectedly. That could be a feature though
  // were the lazy concat is used to set a format, and then strings are swapped
  // out for mass processing data.
  LastString data_;
  lazy_string_concat_helper<Strings...> tail_;

 public:
  lazy_string_concat_helper(LastString data,
                            lazy_string_concat_helper<Strings...> tail)
      : data_(data), tail_(tail) {}
  int size() const { return data_.size() + tail_.size(); }

  template <typename It>
  void save(It end) const {
    // The structure stores data starting at the last concatinated string.
    const auto begin = end - data_.size();
    std::copy(data_.cbegin(), data_.cend(), begin);
    tail_.save(begin);
  }

  operator std::string() const {
    std::string result(size(), '\0');
    save(result.end());
    return result;
  }

  lazy_string_concat_helper<std::string, LastString, Strings...> operator+(
      const std::string& other) const {
    return lazy_string_concat_helper<std::string, LastString, Strings...>(
        other, *this);
  }
};

// Don't forget the base case!
template <>
class lazy_string_concat_helper<> {
 public:
  lazy_string_concat_helper() {}

  int size() const { return 0; }

  template <typename It>
  void save(It) const {}

  lazy_string_concat_helper<std::string> operator+(
      const std::string& other) const {
    return lazy_string_concat_helper<std::string>(other, *this);
  }
};

// Since we std::string doesn't allow us to overload the '+' operator, we need
// to append to an existing lazy_string_concat_helper.
lazy_string_concat_helper<> lazy_concat;

}  // namespace

//=============================================================================
int FPInCppCh6::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Scratch pad from Chapter 6        ####";
  LOG(INFO) << "###################################################";

  {  // lazy_eval tests.
    LOG(INFO) << "Lazy eval tests";
    LOG(INFO) << "Create foo, of type lazy_eval<(int) -> int>. This function "
                 "should not print \"lazy eval\".";
    auto foo = make_lazy_eval([]() {
      LOG(INFO) << "lazy eval";
      return 5;
    });

    LOG(INFO) << "Assign foo to an int. This should cast lazy_eval<> to an int "
                 "implicitly, and we should see \"lazy eval\" printed.";

    int bar = foo;

    LOG(INFO) << "Now assign foo to another int. Here we should not see \"lazy "
                 "eval\" printed, since the return value is cached.";

    int baz = foo;

    // Get rid of unused variable errors.
    bar = baz;
    baz = bar;
  }

  {  // memoize tests.
    LOG(INFO) << "###################################################";
    LOG(INFO) << "make_memoized() tests.";

    // Derefence the lambda to get to the function.
    auto foo_memo = make_memoized(*[](int x) {
      LOG(INFO) << "Working on value: " << x;
      return x;
    });
    LOG(INFO) << "First run of make memoized on value of 5.";

    foo_memo(5);

    LOG(INFO) << "Second run on value of 5. No print out.";

    foo_memo(5);

    LOG(INFO) << "First run of make memoized on value of 6. Print out.";

    foo_memo(6);

    LOG(INFO) << "Third run on value of 5. No print out.";

    foo_memo(5);
  }

  {  // memoize levensthein distance per recursive step.
    LOG(INFO) << "###################################################";
    LOG(INFO) << "Levensthein distance tests.";
    std::string one_a = "cat condo";
    std::string one_b = "dog houses";
    LOG(INFO) << "There should be a lot of work to find the levensthein "
                 "distance this first run.";
    int result =
        LevenshteinDistanceMemo(one_a.size(), one_b.size(), one_a, one_b);

    LOG(INFO) << "Got the resulting distance from a: " << one_a
              << " and b: " << one_b << " was: " << result << " edits away.";

    LOG(INFO) << "There should be no work to find the levensthein distance "
                 "this second run.";
    std::string two_a = "cat";
    std::string two_b = "dog";
    result = LevenshteinDistanceMemo(two_a.size(), two_b.size(), two_a, two_b);

    LOG(INFO) << "Got the resulting distance from a: " << two_a
              << " and b: " << two_b << " was: " << result << " edits away.";
  }

  {  // lazy_string_concat tests.
    LOG(INFO) << "###################################################";
    LOG(INFO) << "lazy_string_concat_helper tests.";

    std::string test1 = "lazy";
    std::string test2 = "string";
    std::string test3 = "concat";
    std::string test4 = "test";

    std::string combined = lazy_concat + "This is a test of " + test1 + "_" +
                           test2 + "_" + test3 + "_" + test4;

    LOG(INFO) << "Result stored in combined: " << combined;

    LOG(INFO) << "Result for concat: "
              << std::string(lazy_concat + test1 + "_" + test2 + "_" + test3 +
                             "_" + test4);
  }

  return 0;
}
}  // namespace fpic_modules
