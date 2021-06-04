// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch7.h"

#include <glog/logging.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh7::FPInCppCh7(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh7::Deserialize(tools::CSVParser& /*params*/) {
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

std::string name(const Person& person) { return person.name; }

// Merging of two collections
struct entry {
  std::string name;
  int count;
  entry(std::string name_, int count_) : name(name_), count(count_) {}
};

std::vector<entry> MergeCollections(const std::vector<entry>& collection_1,
                                    const std::vector<entry>& collection_2) {
  std::vector<entry> result{collection_1};

  result.reserve(collection_1.size() + collection_2.size());
  result.insert(result.end(), collection_2.begin(), collection_2.end());

  // Sort the new merged collection by name.
  // Sepcifying a comparator here is just making the struct robust agaisnt
  // reorganization.
  std::ranges::sort(result,
                    [](auto& lhs, auto& rhs) { return lhs.name < rhs.name; });

  bool first = true;
  entry temp = result[result.size() - 1];

  // Merge the count of elements with the same name. Do this operation backwards
  // and accumulate the count in the first element. This will allow us to use
  // std::unique later on which will preserve the first of many elements. IE.
  // Original: {{a:5},{a:1},{a:3}}
  // Merged:   {{a:9},{a:4},{a:3}}
  // Unique:   {{a:9}}
  for (auto& curr_ent : result | std::views::reverse) {
    if (first) {
      first = false;
      continue;
    }
    if (0 == curr_ent.name.compare(temp.name)) {
      curr_ent.count = curr_ent.count + temp.count;
    }
    temp = curr_ent;
  }

  // Use unique to preserve only the first entry which will have the total for
  // all entries.
  auto removable = std::ranges::unique(
      result, [](auto& lhs, auto& rhs) { return lhs.name == rhs.name; });
  result.erase(removable.begin(), removable.end());

  // Sort by total count.
  std::ranges::sort(result,
                    [](auto& lhs, auto& rhs) { return lhs.count > rhs.count; });

  return result;
}
}  // namespace

//=============================================================================
int FPInCppCh7::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Scratch pad from Chapter 7        ####";
  LOG(INFO) << "###################################################";

  LOG(INFO) << "Working with our people structs and std::range tests.";

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

  {  // All female names.

    // This is a lot like the work done in fpinccpsh2.cpp, but more efficient.
    // With ranges a smart proxy iterator is created, and the filter and
    // transform are linked up and evaluated in a lazt fashion. That means that
    // we will traverse the poeple vector once, and only pass the elements that
    // return true from is_female() to name(), and finally to our for loop's
    // temp.
    LOG(INFO) << "All the female names are: ";
    for (auto person_name :
         people | std::views::filter(is_female) | std::views::transform(name)) {
      LOG(INFO) << "   " << person_name;
    }
  }

  {  // All not female names.
    LOG(INFO) << "All the not female names are: ";
    for (auto person_name :
         people | std::views::filter([](auto&& person) {
           // Here I am perfect forwarding person.
           return false == is_female(std::forward<decltype(person)>(person));
         }) | std::views::transform(name)) {
      LOG(INFO) << "   " << person_name;
    }
  }

  LOG(INFO) << "###################################################";
  LOG(INFO) << "Find the peak with std::range test.";

  {  // Find the peak of a strictly increasing then decreasing vector.
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 4, 3, 2};

    auto peak = std::ranges::adjacent_find(numbers, std::ranges::greater());

    if (peak != numbers.end()) {
      LOG(INFO) << "Found peak at: " << std::distance(numbers.begin(), peak);
    } else {
      LOG(INFO) << "No Peak found";
    }
  }

  LOG(INFO) << "###################################################";
  LOG(INFO) << "Merging key:value stores tests.";

  // Given two vectors of key:count, sorted by count, return one list sorted
  // by count after merging.

  // Helper for printing out the vector of entrys.
  auto print_help = [](const std::vector<entry>& vec) {
    std::stringstream serialized;
    serialized << "{";
    for (auto& ent : vec) {
      serialized << "{" << ent.name << ", " << std::to_string(ent.count) << "}";
    }
    serialized << "}";
    return serialized.str();
  };

  {
    // Front merge
    std::vector<entry> collection_1{{"a", 30}, {"b", 5}};
    std::vector<entry> collection_2{{"a", 20}, {"c", 7}};

    LOG(INFO) << "Merge at the begining.";
    LOG(INFO) << "Merge: " << print_help(collection_1) << " and "
              << print_help(collection_2);
    LOG(INFO) << "Expect: {{a, 50}{c, 7}{b, 5}}";

    auto result = MergeCollections(collection_1, collection_2);
    LOG(INFO) << "Result: " << print_help(result);
  }

  {
    // Middle merge
    std::vector<entry> collection_1{{"a", 30}, {"b", 5}};
    std::vector<entry> collection_2{{"c", 20}, {"b", 7}};

    LOG(INFO) << "Merge in the middle.";
    LOG(INFO) << "Merge: " << print_help(collection_1) << " and "
              << print_help(collection_2);
    LOG(INFO) << "Expect: {{a, 30}{c, 20}{b, 12}}";

    auto result = MergeCollections(collection_1, collection_2);
    LOG(INFO) << "Result: " << print_help(result);
  }

  {
    // End merge
    std::vector<entry> collection_1{{"a", 30}, {"c", 5}};
    std::vector<entry> collection_2{{"b", 20}, {"c", 7}};

    LOG(INFO) << "Merge at the end.";
    LOG(INFO) << "Merge: " << print_help(collection_1) << " and "
              << print_help(collection_2);
    LOG(INFO) << "Expect: {{a, 30}{b, 20}{c, 12}}";
    auto result = MergeCollections(collection_1, collection_2);
    LOG(INFO) << "Result: " << print_help(result);
  }

  return 0;
}
}  // namespace fpic_modules
