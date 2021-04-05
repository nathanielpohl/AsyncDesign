// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch7.h"

#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh7::FPInCppCh7(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh7::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {}  // namespace

//=============================================================================
int FPInCppCh7::Execute() {
  std::cout << "###################################################"
            << std::endl;
  std::cout << "####         Scratch pad from Chapter 7        ####"
            << std::endl;
  std::cout << "###################################################"
            << std::endl;

  {  // lazy_eval tests.
    /*std::cout << "Lazy eval tests" << std::endl;
    std::cout << "Create foo, of type lazy_eval<(int) -> int>. This function\n"
                 "should not print \"lazy eval\"."
              << std::endl;
    auto foo = make_lazy_eval([]() {
      std::cout << "lazy eval" << std::endl;
      return 5;
    });
    std::cout << std::endl;

    std::cout
        << "Assign foo to an int. This should cast lazy_eval<> to an int \n"
           "implicitly, and we should see \"lazy eval\" printed."
        << std::endl
        << std::endl;

    int bar = foo;
    std::cout << std::endl;

    std::cout
        << "Now assign foo to another int. Here we should not see \"lazy \n"
           "eval\" printed, since the return value is cached."
        << std::endl;

    int baz = foo;
    std::cout << std::endl;

    // Get rid of unused variable errors.
    bar = baz;
    baz = bar;*/

    std::cout << std::endl;
  }

  std::cout << std::endl;

  return 0;
}
}  // namespace fpic_modules
