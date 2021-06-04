// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch2.h"

#include <glog/logging.h>

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh2::FPInCppCh2(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh2::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
struct Person {
  std::string name;
  std::string gender;
  int number;
};

bool is_female(const Person& person) {
  return 0 == person.gender.compare("Female");
}

bool is_not_female(const Person& person) {
  return 0 != person.gender.compare("Female");
}

std::string name(const Person& person) { return person.name; }
}  // namespace

//=============================================================================
int FPInCppCh2::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Scratch pad from Chapter 2        ####";
  LOG(INFO) << "###################################################";

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

  // All female names.
  {
    LOG(INFO) << "All female names.";
    std::vector<Person> females;
    std::copy_if(people.begin(), people.end(), std::back_inserter(females),
                 is_female);
    std::vector<std::string> female_names(females.size());
    std::transform(females.cbegin(), females.cend(), female_names.begin(),
                   name);
    LOG(INFO) << "All the female names are: ";
    for (auto& person_name : female_names) {
      LOG(INFO) << "   " << person_name;
    }

    LOG(INFO) << "\n";
  }

  // All not female names.
  {
    LOG(INFO) << "All not female names.";
    std::vector<Person> not_females;
    std::copy_if(people.begin(), people.end(), std::back_inserter(not_females),
                 is_not_female);
    std::vector<std::string> not_female_names(not_females.size());
    std::transform(not_females.cbegin(), not_females.cend(),
                   not_female_names.begin(), name);
    LOG(INFO) << "All the not female names are: ";
    for (auto& person_name : not_female_names) {
      LOG(INFO) << "   " << person_name;
    }

    LOG(INFO) << "\n";
  }

  // More efficient split of female and not female.
  {
    LOG(INFO) << "More efficient split of female and not female.";
    auto people_copy = people;
    auto first_not_female = std::stable_partition(people_copy.begin(),
                                                  people_copy.end(), is_female);
    std::vector<std::string> female_names(
        std::distance(people_copy.begin(), first_not_female));
    std::vector<std::string> not_female_names(
        std::distance(first_not_female, people_copy.end()));

    LOG(INFO) << "Female count: " << std::to_string(female_names.capacity());
    LOG(INFO) << "Not female count: "
              << std::to_string(not_female_names.capacity());

    std::transform(people_copy.begin(), first_not_female, female_names.begin(),
                   name);
    std::transform(first_not_female, people_copy.end(),
                   not_female_names.begin(), name);

    LOG(INFO) << "All the female names are: ";
    for (auto& person_name : female_names) {
      LOG(INFO) << "   " << person_name;
    }

    LOG(INFO) << "All the not female names are: ";
    for (auto& person_name : not_female_names) {
      LOG(INFO) << "   " << person_name;
    }

    LOG(INFO) << '\n';
  }

  return 0;
}
}  // namespace fpic_modules
