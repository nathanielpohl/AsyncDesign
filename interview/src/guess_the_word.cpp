// This file contains the class definition for guess the word problem.
#include "interview/guess_the_word.h"

#include <glog/logging.h>

#include <algorithm>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

namespace interview {

//=============================================================================
GuessTheWord::GuessTheWord(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void GuessTheWord::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
This is an interactive problem.

You are given an array of unique strings wordlist where wordlist[i] is 6 letters
long, and one word in this list is chosen as secret.

You may call Master.guess(word) to guess a word. The guessed word should have
type string and must be from the original list with 6 lowercase letters.

This function returns an integer type, representing the number of exact matches
(value and position) of your guess to the secret word. Also, if your guess is
not in the given wordlist, it will return -1 instead.

For each test case, you have exactly 10 guesses to guess the word. At the end of
any number of calls, if you have made 10 or fewer calls to Master.guess and at
least one of these guesses was secret, then you pass the test case.



Example 1:

Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"],
numguesses = 10
Output: You guessed the secret word correctly.
Explanation:
master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6
matches. master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
We made 5 calls to master.guess and one of them was the secret, so we pass the
test case. Example 2:

Input: secret = "hamada", wordlist = ["hamada","khaled"], numguesses = 10
Output: You guessed the secret word correctly.


Constraints:

1 <= wordlist.length <= 100
wordlist[i].length == 6
wordlist[i] consist of lowercase English letters.
All the strings of wordlist are unique.
secret exists in wordlist.
numguesses == 10
  */

// This problem is from leetcode. I would not have named my class this, but for
// easy of running the leetcode autotester I'm keeping this name. I would also
// change the

// This is the Master's API interface.
class Master {
 public:
  Master(std::vector<std::string> arr, int secret_index)
      : arr_(arr), secret_(arr[secret_index]) {
    std::sort(arr_.begin(), arr_.end());
  }

  int guess(std::string word) {
    auto it = std::lower_bound(arr_.begin(), arr_.end(), word);

    // Check to see if the word is in the wordlist.
    if (it == arr_.end() || word.compare(*it)) {
      LOG(INFO) << "NOT FOUND IN WORDLIST!";
      return -1;
    }

    // See how many positions and letters match.
    int match = 0;

    for (int ii = 0; ii < (int)word.size(); ++ii) {
      if (word[ii] == secret_[ii]) {
        match++;
      }
    }
    return match;
  }

 private:
  std::vector<std::string> arr_;
  std::string secret_;
};

class Solution {
 public:
  int MatchingLetters(const std::string& word_one,
                      const std::string& word_two) {
    int match = 0;

    for (int ii = 0; ii < (int)word_one.size(); ++ii) {
      if (word_one[ii] == word_two[ii]) {
        match++;
      }
    }
    return match;
  }

  int IndexOfWordWithHighestOccurancyLetter(
      const std::vector<std::string>& wordlist) {
    // Base case, we get a list of one word.
    if (wordlist.size() == 1) {
      return 0;
    }

    std::vector<std::unordered_map<char, int>> letter_counts(6);

    // Count all letters in all positions of each word.
    for (auto& word : wordlist) {
      for (int ii = 0; ii < 6; ++ii) {
        letter_counts[ii][word[ii]] += 1;
      }
    }

    // Find the highest occuring letter out of all positions it could be in a
    // word.
    char highest_occuring_letter = 'A';
    int highest_ocrruring_letter_count = 0;
    int highest_occuring_letter_index = 0;
    for (int ii = 0; ii < 6; ++ii) {
      auto& letter_map = letter_counts[ii];
      char letter = 'A';
      int letter_count = 0;

      for (auto& [current_letter, current_count] : letter_map) {
        if (current_count > letter_count) {
          letter = current_letter;
          letter_count = current_count;
        }
      }

      // Ignore the letter if all the words in the list have the same letter in
      // the same position. eg axxxxx, ayyyyy, azzzzz...
      if (letter_count != (int)wordlist.size() &&
          letter_count > highest_ocrruring_letter_count) {
        highest_occuring_letter = letter;
        highest_ocrruring_letter_count = letter_count;
        highest_occuring_letter_index = ii;
      }
    }

    // Find and return the index of a word that has the highest occuring letter
    // in it.
    int index = 0;
    for (; index < (int)wordlist.size(); index++) {
      auto& word = wordlist[index];
      if (word[highest_occuring_letter_index] == highest_occuring_letter) {
        break;
      }
    }

    return index;
  }

  std::vector<std::string> AllWordsWithMatches(
      const std::vector<std::string>& word_list, const std::string& guess_word,
      int guess_matches, bool include = true) {
    std::vector<std::string> results;
    for (const auto& word : word_list) {
      int matches = MatchingLetters(guess_word, word);
      if (include) {
        if (matches == guess_matches) {
          results.emplace_back(word);
        }
      } else {
        if (matches == 0) {
          results.emplace_back(word);
        }
      }
    }

    return results;
  }

  void findSecretWord(const std::vector<std::string>& wordlist, Master& box) {
    std::vector<std::string> possible_words(wordlist);

    // Only 10 guesses are allowed.
    for (int ii = 0; ii < 10; ++ii) {
      // Always guess a random word.
      int index = IndexOfWordWithHighestOccurancyLetter(possible_words);
      int matches = box.guess(possible_words[index]);

      if (matches == 6) {
        LOG(INFO) << "Found secret!!: " << possible_words[index];
        break;
      }

      if (matches > 0) {
        // Generate a new list of words that macth our current word in the same
        // number of positions that we got back from our guess.
        possible_words =
            AllWordsWithMatches(possible_words, possible_words[index], matches);

        LOG(INFO) << "Generated a new list of size: " << possible_words.size()
                  << " matches: " << matches;
      } else if (matches == 0) {
        // Remove any word that has a match since it won't be the word we are
        // looking for.
        possible_words = AllWordsWithMatches(
            possible_words, possible_words[index], matches, false);

        LOG(INFO) << "Generating a new excluding list of size: "
                  << possible_words.size();
      } else {
        // Delete the first word, so the our next iteration we try
        // possible_strings[1].
        possible_words.erase(possible_words.begin() + index);

        LOG(INFO) << "Deleted first element, not in wordlist. New array.size: "
                  << possible_words.size();
      }
    }
  }
};

}  // namespace

//=============================================================================
int GuessTheWord::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####               Guess The Word              ####";
  LOG(INFO) << "###################################################";

  {
    std::vector<std::string> arr{"ccbazz", "eiowzz", "abcczz", "acckzz"};
    Master box(arr, arr.size() - 1);
    Solution mine;
    LOG(INFO) << "Test 1";
    mine.findSecretWord(arr, box);
  }

  {
    std::vector<std::string> arr{"khaled", "hamada"};
    Master box(arr, 1);
    Solution mine;
    LOG(INFO) << "Test 2";
    mine.findSecretWord(arr, box);
  }

  {
    std::vector<std::string> arr{"ccbazz", "eiowzz", "abcczz", "acckzz"};
    std::vector<std::string> arr_with_no_valid_guesses{"aaaaaa", "bbbbbb",
                                                       "acckzz"};
    Master box(arr, arr.size() - 1);
    Solution mine;
    LOG(INFO) << "Test 3";
    mine.findSecretWord(arr_with_no_valid_guesses, box);
  }

  {
    std::vector<std::string> arr{"ccbazz", "eiowzz", "abcczz", "acckzz",
                                 "thmsbe", "loolrr", "cooyyd", "qqqwca",
                                 "dfytbd", "oolsme", "coolbe"};
    Master box(arr, arr.size() - 1);
    Solution mine;
    LOG(INFO) << "Test 4";
    mine.findSecretWord(arr, box);
  }

  {
    std::vector<std::string> arr{
        "eykdft", "gjeixr", "eksbjm", "mxqhpk", "tjplhf", "ejgdra", "npkysm",
        "jsrsid", "cymplm", "vegdgt", "jnhdvb", "jdhlzb", "sgrghh", "jvydne",
        "laxvnm", "xbcliw", "emnfcw", "pyzdnq", "vzqbuk", "gznrnn", "robxqx",
        "oadnrt", "kzwyuf", "ahlfab", "zawvdf", "edhumz", "gkgiml", "wqqtla",
        "csamxn", "bisxbn", "zwxbql", "euzpol", "mckltw", "bbnpsg", "ynqeqw",
        "uwvqcg", "hegrnc", "rrqhbp", "tpfmlh", "wfgfbe", "tpvftd", "phspjr",
        "apbhwb", "yjihwh", "zgspss", "pesnwj", "dchpxq", "axduwd", "ropxqf",
        "gahkbq", "yxudiu", "dsvwry", "ecfkxn", "hmgflc", "fdaowp", "hrixpl",
        "czkgyp", "mmqfao", "qkkqnz", "lkzaxu", "cngmyn", "nmckcy", "alpcyy",
        "plcmts", "proitu", "tpzbok", "vixjqn", "suwhab", "dqqkxg", "ynatlx",
        "wmbjxe", "hynjdf", "xtcavp", "avjjjj", "fmclkd", "ngxcal", "neyvpq",
        "cwcdhi", "cfanhh", "ruvdsa", "pvzfyx", "hmdmtx", "pepbsy", "tgpnql",
        "zhuqlj", "tdrsfx", "xxxyle", "zqwazc", "hsukcb", "aqtdvn", "zxbxps",
        "wziidg", "tsuxvr", "florrj", "rpuorf", "jzckev", "qecnsc", "rrjdyh",
        "zjtdaw", "dknezk"};
    Master box(arr, 8);
    Solution mine;
    LOG(INFO) << "Test 5";
    mine.findSecretWord(arr, box);
  }

  {
    std::vector<std::string> arr{
        "gaxckt", "trlccr", "jxwhkz", "ycbfps", "peayuf", "yiejjw", "ldzccp",
        "nqsjoa", "qrjasy", "pcldos", "acrtag", "buyeia", "ubmtpj", "drtclz",
        "zqderp", "snywek", "caoztp", "ibpghw", "evtkhl", "bhpfla", "ymqhxk",
        "qkvipb", "tvmued", "rvbass", "axeasm", "qolsjg", "roswcb", "vdjgxx",
        "bugbyv", "zipjpc", "tamszl", "osdifo", "dvxlxm", "iwmyfb", "wmnwhe",
        "hslnop", "nkrfwn", "puvgve", "rqsqpq", "jwoswl", "tittgf", "evqsqe",
        "aishiv", "pmwovj", "sorbte", "hbaczn", "coifed", "hrctvp", "vkytbw",
        "dizcxz", "arabol", "uywurk", "ppywdo", "resfls", "tmoliy", "etriev",
        "oanvlx", "wcsnzy", "loufkw", "onnwcy", "novblw", "mtxgwe", "rgrdbt",
        "ckolob", "kxnflb", "phonmg", "egcdab", "cykndr", "lkzobv", "ifwmwp",
        "jqmbib", "mypnvf", "lnrgnj", "clijwa", "kiioqr", "syzebr", "rqsmhg",
        "sczjmz", "hsdjfp", "mjcgvm", "ajotcx", "olgnfv", "mjyjxj", "wzgbmg",
        "lpcnbj", "yjjlwn", "blrogv", "bdplzs", "oxblph", "twejel", "rupapy",
        "euwrrz", "apiqzu", "ydcroj", "ldvzgq", "zailgu", "xgqpsr", "wxdyho",
        "alrplq", "brklfk"};
    Master box(arr, 45);
    Solution mine;
    LOG(INFO) << "Test 6";
    mine.findSecretWord(arr, box);
  }

  {
    std::vector<std::string> arr{
        "wichbx", "oahwep", "tpulot", "eqznzs", "vvmplb", "eywinm", "dqefpt",
        "kmjmxr", "ihkovg", "trbzyb", "xqulhc", "bcsbfw", "rwzslk", "abpjhw",
        "mpubps", "viyzbc", "kodlta", "ckfzjh", "phuepp", "rokoro", "nxcwmo",
        "awvqlr", "uooeon", "hhfuzz", "sajxgr", "oxgaix", "fnugyu", "lkxwru",
        "mhtrvb", "xxonmg", "tqxlbr", "euxtzg", "tjwvad", "uslult", "rtjosi",
        "hsygda", "vyuica", "mbnagm", "uinqur", "pikenp", "szgupv", "qpxmsw",
        "vunxdn", "jahhfn", "kmbeok", "biywow", "yvgwho", "hwzodo", "loffxk",
        "xavzqd", "vwzpfe", "uairjw", "itufkt", "kaklud", "jjinfa", "kqbttl",
        "zocgux", "ucwjig", "meesxb", "uysfyc", "kdfvtw", "vizxrv", "rpbdjh",
        "wynohw", "lhqxvx", "kaadty", "dxxwut", "vjtskm", "yrdswc", "byzjxm",
        "jeomdc", "saevda", "himevi", "ydltnu", "wrrpoc", "khuopg", "ooxarg",
        "vcvfry", "thaawc", "bssybb", "ccoyyo", "ajcwbj", "arwfnl", "nafmtm",
        "xoaumd", "vbejda", "kaefne", "swcrkh", "reeyhj", "vmcwaf", "chxitv",
        "qkwjna", "vklpkp", "xfnayl", "ktgmfn", "xrmzzm", "fgtuki", "zcffuv",
        "srxuus", "pydgmq"};
    Master box(arr, 80);
    Solution mine;
    LOG(INFO) << "Test 7";
    mine.findSecretWord(arr, box);
  }

  {
    std::vector<std::string> arr{
        "abcdef", "acdefg", "adefgh", "aefghi", "afghij", "aghijk", "ahijkl",
        "aijklm", "ajklmn", "aklmno", "almnoz", "anopqr", "azzzzz"};
    Master box(arr, 12);
    Solution mine;
    LOG(INFO) << "Test 8";
    mine.findSecretWord(arr, box);
  }

  return 0;
}
}  // namespace interview
