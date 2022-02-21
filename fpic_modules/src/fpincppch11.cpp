// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch11.h"

#include <glog/logging.h>

#include <list>
#include <numeric>
#include <ranges>
#include <string>
#include <tuple>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh11::FPInCppCh11(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh11::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
// Checking on types at compile time.
// Implementing my own remove_reference_t. Default case is there is no
// refernce.
template <typename T>
struct remove_reference_mine {
  using type = T;
};
// Specialize for lref.
template <typename T>
struct remove_reference_mine<T&> {
  using type = T;
};
// Specialize for rref.
template <typename T>
struct remove_reference_mine<T&&> {
  using type = T;
};
// Convinece metafunction that acts like the ..._t(), so we don't have to type
// remove_refernce_mine<T>::type everywhere.
template <typename T>
using remove_reference_mine_t = typename remove_reference_mine<T>::type;

//=============================================================================
// Checks on what type is in a container.
template <typename T>
using contained_type_t = std::remove_cv_t<
    remove_reference_mine_t<decltype(*begin(std::declval<T>()))>>;

//=============================================================================
// Use our compile time type traits to fill in some informatoin for
// accumulate().
template <typename C, typename R = contained_type_t<C>>
R sum_iterable(const C& collection) {
  return std::accumulate(begin(collection), end(collection), R());
}

// Most well behaved collections have a line "using value_type = T" in them.
// Since some collections will return wrapped types (think something like
// std::optional) it's better to use C::value_type since you might get a wrapper
// type with contained_type_t instead of the item it contains.
template <typename C, typename R = typename C::value_type>
R sum_collection(const C& collection) {
  return std::accumulate(begin(collection), end(collection), R());
}

//=============================================================================
// We can test at compilation time if a collection has a value_type, and switch
// on which sum function, listed above, that we want to use.
// Always start with the general case, there is no "using value_type = T"
// defined on the collection/container/wrapper. In this case return false_type.
template <typename C, typename = std::void_t<>>
struct has_value_type : std::false_type {};
// Specialize the case where value_type is defined to return true_type.
// void_t<...> will return void and compile as long as all types contained are
// valid.
template <typename C>
struct has_value_type<C, std::void_t<typename C::value_type>> : std::true_type {
};

//=============================================================================
// We can test at compilation time if a collection is iterable or not by testing
// that we can derefernce what is returned by begin(), and test that the
// collection has end() defined.
template <typename C, typename = std::void_t<>>
struct is_iterable : std::false_type {};
// Specialize the case where we can derefernce begin() and the type has an
// end().
template <typename C>
struct is_iterable<C, std::void_t<decltype(*begin(std::declval<C>())),
                                  decltype(end(std::declval<C>()))>>
    : std::true_type {};

//=============================================================================
// We can write a smart compile time switcher on what sum function to call now
// that we can check if the type have value_type or not.
template <typename C>
auto sum_mine(const C& collection) {
  // Use "if constexpr" here so that at compilation time the compiler will
  // choose which branch it wants to compile for the collection, and not have
  // the program at runtime choose. Since collections that don't have value_type
  // defined on them will fail calling sum_collection, we can't use a regular
  // "if" here since it wouldn't allow for this code to 1le since of invalid
  // syntax.
  if constexpr (has_value_type<C>()) {
    return sum_collection(collection);
  } else if constexpr (is_iterable<C>()) {
    return sum_iterable(collection);
  } else {
    // Nothing! We can't sum if we can't use value_type or conatianed_type_t().
  }
}

//=============================================================================
// We can curry functions with Template Meta Programming. All we have to do is
// keep track of previous arguments in a touple, and the funciton that we want
// to call. Once we have all the arguments we need, we can return the result of
// calling the function with all saved arguments.
template <typename Function, typename... CapturedArgs>
class Curried {
 private:
  using CapturedArgsTuple = std::tuple<std::decay_t<CapturedArgs>...>;

  template <typename... Args>
  static auto CaptureByCopy(Args&&... args) {
    return std::tuple<std::decay_t<Args>...>(std::forward<Args>(args)...);
  }

 public:
  // This constructor that will most likely be called by the user.
  Curried(Function function, CapturedArgs... args)
      : function_(function),
        captured_args_(CaptureByCopy(std::move(args)...)) {}

  // This constructor is easiest for operator() to call.
  Curried(Function function, std::tuple<CapturedArgs...> args)
      : function_(function), captured_args_(std::move(args)) {}

  template <typename... NewArgs>
  auto operator()(NewArgs&&... args) const {
    auto new_args = CaptureByCopy(std::forward<NewArgs>(args)...);
    auto all_args = std::tuple_cat(captured_args_, std::move(new_args));

    if constexpr (std::is_invocable<Function, CapturedArgs..., NewArgs...>()) {
      // is_invocable() says that the types of the args line up with the
      // function signature, so we can return a result.
      return std::apply(function_, all_args);
    } else {
      // If we can't invoke, than create a new curried function with that new
      // args appended on.
      return Curried<Function, CapturedArgs..., NewArgs...>(function_,
                                                            all_args);
    }
  }

 private:
  Function function_;
  std::tuple<CapturedArgs...> captured_args_;
};
}  // namespace

//=============================================================================
int FPInCppCh11::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Scratch pad from Chapter 11       ####";
  LOG(INFO) << "###################################################";

  {
    // Test remove_refernce_mine_t.
    static_assert(std::is_same<int, remove_reference_mine_t<int>>(),
                  "remove_reference_mine_t<int> should go to int.");
    static_assert(std::is_same<int, remove_reference_mine_t<int&>>(),
                  "remove_reference_mine_t<int&> should go to int.");
    static_assert(std::is_same<int, remove_reference_mine_t<int&&>>(),
                  "remove_reference_mine_t<int&&> should go to int.");

    // This statis_assert will stop comilation since of the bool.
    // static_assert(std::is_same<bool, remove_reference_mine_t<int>>(),
    //              "remove_reference_mine_t<int> should go to int.");

    LOG(INFO) << "All static_assert for remove_refernce_mine_t<T> passed at "
                 "compilation time.";
  }

  {
    // Test contained type.
    static_assert(std::is_same<int, contained_type_t<std::vector<int>>>(),
                  "std::vector<int> should contain int.");
    static_assert(
        std::is_same<std::string, contained_type_t<std::list<std::string>>>(),
        "std::list<std::string> should contain std::string.");

    // This static_assert will stop compilation since of the bool.
    // static_assert(std::is_same<bool, contained_type_t<std::vector<int>>>(),
    //              "std::vector<int> should contain int.");

    LOG(INFO) << "All static_asserts for contained_type_t<T> passed at "
                 "compilation time.";
  }

  {
    // Test sum functions.
    std::vector<int> values{1, 4, 5, 2, 56, 3};
    auto iterable_result = sum_iterable(values);
    auto collection_results = sum_collection(values);

    if (iterable_result == collection_results) {
      LOG(INFO)
          << "Got the same result for sum_iterable() and sum_collection(): "
          << iterable_result;
    } else {
      LOG(ERROR) << "Got sum_iterable(): " << iterable_result
                 << " and sume_collection(): " << collection_results;
    }
  }

  {
    // Test sum switcher.
    std::vector<int> values{3, 12, 3, 13, 5};

    auto result = sum_mine(values);

    LOG(INFO) << "sum_mine() returned the result: " << result;
  }

  {
    // Test curried.
    auto test = [](int a, std::string b) {
      LOG(INFO) << "\tNumber: " << a << " String: " << b;
    };
    auto test_curried = Curried{test};

    test_curried(5)("five");

    auto test_curried_6 = test_curried(6);
    test_curried_6("six");
    test_curried_6("seven");
  }

  return 0;
}
}  // namespace fpic_modules
