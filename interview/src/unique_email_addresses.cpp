// This file contains the class definition for checking for unique email
// addresses.
#include "interview/unique_email_addresses.h"

#include <glog/logging.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

namespace interview {

//=============================================================================
UniqueEmailAddresses::UniqueEmailAddresses(std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void UniqueEmailAddresses::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
Every valid email consists of a local name and a domain name, separated by the
'@' sign. Besides lowercase letters, the email may contain one or more '.' or
'+'.

- For example, in "alice@leetcode.com", "alice" is the local name, and
"leetcode.com" is the domain name.

If you add periods '.' between some
characters in the local name part of an email address, mail sent there will be
forwarded to the same address without dots in the local name. Note that this
rule does not apply to domain names.

- For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the
same email address.

If you add a plus '+' in the local name, everything after
the first plus sign will be ignored. This allows certain emails to be filtered.
Note that this rule does not apply to domain names.

- For example, "m.y+name@email.com" will be forwarded to "my@email.com".

It is possible to use both of these rules at the same time.

Given an array of strings emails where we send one email to each email[i],
return the number of different addresses that actually receive mails.

Example 1:

Input: emails =
["test.email+alex@leetcode.com", "test.e.mail+bob.cathy@leetcode.com",
"testemail+david@lee.tcode.com"]
Output: 2 Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com"
actually receive mails.

Example 2:

Input: emails = ["a@leetcode.com", "b@leetcode.com", "c@leetcode.com"]
Output: 3


Constraints:

1 <= emails.length <= 100
1 <= emails[i].length <= 100
email[i] consist of lowercase English letters, '+', '.' and '@'.
Each emails[i] contains exactly one '@' character.
All local and domain names are non-empty.
Local names do not start with a '+' character.
 */

class Solution {
 public:
  std::string ResolveEmail(const std::string& email) {
    std::stringstream resolved_email;

    bool pre_at = true;
    bool pre_plus = true;
    for (auto letter : email) {
      if (letter == '@') {
        pre_at = false;
      }

      if (pre_at) {
        if (letter == '+') {
          pre_plus = false;
        }

        if (pre_plus == false) {
          continue;
        }

        if (letter == '.') {
          continue;
        }
      }

      resolved_email << letter;
    }

    return resolved_email.str();
  }

  int numUniqueEmails(std::vector<std::string>& emails) {
    std::unordered_set<std::string> resolved_emails;

    for (const auto& email : emails) {
      resolved_emails.insert(ResolveEmail(email));
    }

    return resolved_emails.size();
  }
};

}  // namespace

//=============================================================================
int UniqueEmailAddresses::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####           Unique Email Addresses          ####";
  LOG(INFO) << "###################################################";

  {
    std::vector<std::string> email_addresses{
        "test@gmail.com", ".test@gmail.com", "..test@gmail.com",
        "test.@gmail.com", "test..@gmail.com"};
    Solution mine;
    LOG(INFO) << "Should be 1: " << mine.numUniqueEmails(email_addresses);
  }

  {
    std::vector<std::string> email_addresses{
        "test@gmail.com",       "test+@gmail.com",
        "test++@gmail.com",     "test+blah+@gmail.com",
        "test++blah@gmail.com", "test+blah+blah@gmail.com"};
    Solution mine;
    LOG(INFO) << "Should be 1: " << mine.numUniqueEmails(email_addresses);
  }

  {
    std::vector<std::string> email_addresses{
        "test.email+alex@leetcode.com", "test.e.mail+bob.cathy@leetcode.com",
        "testemail+david@lee.tcode.com"};
    Solution mine;
    LOG(INFO) << "Should be 2: " << mine.numUniqueEmails(email_addresses);
  }

  {
    std::vector<std::string> email_addresses{"a@leetcode.com", "b@leetcode.com",
                                             "c@leetcode.com"};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.numUniqueEmails(email_addresses);
  }

  return 0;
}
}  // namespace interview
