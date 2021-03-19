// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch3.h"

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh3::FPInCppCh3(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh3::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
struct Person {
  std::string name;
  std::string gender;
  int number;
};

struct Animal {
  std::string type;
  bool is_pet;
  std::string gender;
  int age;
};
}  // namespace

//=============================================================================
int FPInCppCh3::Execute() {
  std::cout << "###################################################"
            << std::endl;
  std::cout << "####         Scratch pad from Chapter 3        ####"
            << std::endl;
  std::cout << "###################################################"
            << std::endl;

  std::vector<Person> people;
  people.reserve(10);
  people.emplace_back("Maria", "Female", 73);
  people.emplace_back("Tom", "Male", 13);
  people.emplace_back("Nathaniel", "Male", 81);
  people.emplace_back("Alex", "Other", 54);
  people.emplace_back("Someone", "Male", 34);
  people.emplace_back("Tester", "Female", 75);
  people.emplace_back("Elon", "Male", 3);
  people.emplace_back("Sara", "Female", 41);
  people.emplace_back("Sussie", "Female", 82);
  people.emplace_back("Bob", "Male", 100);

  std::vector<Animal> animals;
  animals.reserve(3);
  animals.emplace_back("Dog", true, "Male", 13);
  animals.emplace_back("Raccoon", false, "Female", 3);
  animals.emplace_back("Squirrel", false, "Male", 1);

  // Lambdas are default const, but can be mutable.
  {
    // A. Capture count by reference.
    int count = 0;
    auto count_people_1 = [&count](const Person&) { count++; };
    std::for_each(people.cbegin(), people.cend(), count_people_1);
    std::cout << "Person count is: " << std::to_string(count) << std::endl;

    // B. You can define vals for lambdas to use in their capture. This
    // functionality can also be used to std::move things like std::unique_ptr,
    // std::lock, and std::mutex into a lambda.
    auto is_female = [a_gender = "Female"](const Person& person) {
      return 0 == person.gender.compare(a_gender);
    };
    int female_count = count_if(people.cbegin(), people.cend(), is_female);
    std::cout << "Count of females: " << female_count << std::endl;

    // C. Define a val in the lambda capture, and make the lambda mutable so we
    // can update that caputured value.
    auto count_people_2 = [count_2 = 0](const Person&) mutable {
      std::cout << ++count_2 << ' ';
    };
    std::cout << "Counting people: ";
    std::for_each(people.cbegin(), people.cend(), count_people_2);
    std::cout << '\n' << std::endl;
  }

  // Lambdas can work on generics.
  {
    auto is_male = [](auto&& thing) {
      return 0 == thing.gender.compare("Male");
    };
    int male_people_count =
        std::count_if(people.cbegin(), people.cend(), is_male);
    std::cout << "Male person count: " << std::to_string(male_people_count)
              << std::endl;

    int male_animal_count =
        std::count_if(animals.cbegin(), animals.cend(), is_male);
    std::cout << "Male animal count: " << std::to_string(male_animal_count)
              << std::endl;

    std::cout << '\n' << std::endl;
  }

  return 0;
}
}  // namespace fpic_modules
