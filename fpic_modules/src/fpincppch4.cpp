// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "fpic_modules/fpincppch4.h"

#include <glog/logging.h>

#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace fpic_modules {

//=============================================================================
FPInCppCh4::FPInCppCh4(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void FPInCppCh4::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {

std::vector<std::string> words(const std::string& text) {
  std::string line;
  std::vector<std::string> results;
  std::stringstream ss(text);
  while (std::getline(ss, line, ' ')) {
    results.emplace_back(line);
  }

  return results;
}

template <typename C, typename T = typename C::value_type>
std::unordered_map<T, int> count_occurances(const C& collection) {
  std::unordered_map<T, int> results;
  for (const T& item : collection) {
    if (results.find(item) != results.end()) {
      results[item] += 1;
    } else {
      results[item] = 1;
    }
  }
  return results;
}

template <typename C,
          typename P1 =
              typename std::remove_cv<typename C::value_type::first_type>::type,
          typename P2 = typename std::remove_cv<
              typename C::value_type::second_type>::type>
std::vector<std::pair<P2, P1>> reverse_pairs(const C& collection) {
  std::vector<std::pair<P2, P1>> results(collection.size());

  std::transform(collection.begin(), collection.end(), results.begin(),
                 [](const std::pair<const P1, const P2>& p) {
                   return std::make_pair(p.second, p.first);
                 });
  return results;
}

auto sort_by_frequency(const std::vector<std::pair<int, std::string>>& items) {
  auto results = items;
  std::sort(results.begin(), results.end(),
            [](const auto& lhs_p, const auto& rhs_p) {
              return lhs_p.first > rhs_p.first;
            });
  return results;
}

void print_pairs(const std::vector<std::pair<int, std::string>>& items) {
  for (const auto& item : items) {
    LOG(INFO) << std::to_string(item.first) << ", " << item.second;
  }
}

void print_common_words(const std::string& text) {
  return print_pairs(
      sort_by_frequency(reverse_pairs(count_occurances(words(text)))));
}

}  // namespace

//=============================================================================
int FPInCppCh4::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Scratch pad from Chapter 4        ####";
  LOG(INFO) << "###################################################";

  std::string test_str =
      "this is a random string with lot of repeating words to follow this is "
      "is is is is random string length random";

  LOG(INFO) << "test_str: "
            << "\'" << test_str << "\'";
  print_common_words(test_str);

  LOG(INFO) << "Blank str: \'\'";
  print_common_words("");

  return 0;
}
}  // namespace fpic_modules
