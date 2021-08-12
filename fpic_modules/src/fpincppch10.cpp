// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch10.h"

#include <glog/logging.h>

#include <functional>
//#include <iostream>
//#include <numeric>
#include <ranges>
#include <string>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh10::FPInCppCh10(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh10::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
// Functions to turn vector into a functor.
template <typename T, typename F>
auto Transform(const std::vector<T>& input, F function) {
  return input | std::views::transform(function);
}

template <typename T>
std::vector<T> MakeVector(T&& value) {
  return {std::forward<T>(value)};
}

// Function to turn vector into a monad.
// I might need to wait until C++23 to get this working. in C++20 they didn't
// include join or to_vector.
// template <typename T, typename F>
// auto MonadBind(const std::vector<T>& input, F function) {
//  return std::join(transform(input, function));
//}

std::string AddSpace(const std::string& str) { return str + " "; }

}  // namespace

//=============================================================================
int FPInCppCh10::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Scratch pad from Chapter 10       ####";
  LOG(INFO) << "###################################################";

  LOG(INFO) << "###################################################";

  LOG(INFO) << "Functors and Monads";
  LOG(INFO) << "A class template F is a functor if it has transform (or map) "
               "functions defined on it.";
  LOG(INFO) << " - Transforming a functor instance with an identity function "
               "returns the same functor instance.";
  LOG(INFO) << " - Transforming a functor with one function followed by "
               "another is the same as their composite.";
  LOG(INFO) << "Monads  is a functor that has a function defined on it that "
               "removes one layer of nesting.";
  LOG(INFO) << " - mbind() : M<M<T>> -> M<T>";

  {
    // Test for the vector functor and monad.
    std::vector<std::string> vec_of_strings{"this", "is", "a", "test"};
    LOG(INFO) << vec_of_strings.size();
    Transform(vec_of_strings, AddSpace);
    LOG(INFO) << vec_of_strings.size();
    // You can think of MonadBind() like a transform() and join().
    /*auto one_element_vector =
        MonadBind(vec_of_strings, [](const std::string item) { return item;
       });*/
  }

  return 0;
}
}  // namespace fpic_modules
