// This file is where commands are registered.
#pragma once

#include "cmd_modules/checksum.h"
#include "cmd_modules/word_count.h"
#include "cmd_modules/word_freq.h"
#include "fpic_modules/fpincppch10.h"
#include "fpic_modules/fpincppch11.h"
#include "fpic_modules/fpincppch2.h"
#include "fpic_modules/fpincppch3.h"
#include "fpic_modules/fpincppch4.h"
#include "fpic_modules/fpincppch6.h"
#include "fpic_modules/fpincppch7.h"
#include "fpic_modules/fpincppch9.h"
#include "interview/adding_two_numbers.h"
#include "interview/count_complete_tree_nodes.h"
#include "interview/decode_string.h"
#include "interview/exam_room.h"
#include "interview/fruit_into_basket.h"
#include "interview/guess_the_word.h"
#include "interview/longest_increasing_path_matrix.h"
#include "interview/median_of_two_sorted_arrays.h"
#include "interview/most_stones_removed_with_same_row_or_column.h"
#include "interview/odd_even_jump.h"
#include "interview/redundant_connection.h"
#include "interview/unique_email_addresses.h"
#include "interview/valid_number.h"

#define LIST_OF_COMMANDS(COMMAND)                                        \
  COMMAND(cmd_modules, Checksum, "CHECKSUM")                             \
  COMMAND(cmd_modules, WordCount, "WORDCOUNT")                           \
  COMMAND(cmd_modules, WordFreq, "WORDFREQ")                             \
  COMMAND(fpic_modules, FPInCppCh2, "FPICCH2")                           \
  COMMAND(fpic_modules, FPInCppCh3, "FPICCH3")                           \
  COMMAND(fpic_modules, FPInCppCh4, "FPICCH4")                           \
  COMMAND(fpic_modules, FPInCppCh6, "FPICCH6")                           \
  COMMAND(fpic_modules, FPInCppCh7, "FPICCH7")                           \
  COMMAND(fpic_modules, FPInCppCh9, "FPICCH9")                           \
  COMMAND(fpic_modules, FPInCppCh10, "FPICCH10")                         \
  COMMAND(fpic_modules, FPInCppCh11, "FPICCH11")                         \
  COMMAND(interview, AddingTwoNumbers, "ADDINGTWONUMBERS")               \
  COMMAND(interview, CountCompleteTreeNodes, "COUNTCOMPLETETREENODES")   \
  COMMAND(interview, DecodeString, "DECODESTRING")                       \
  COMMAND(interview, ExamRoom, "EXAMROOM")                               \
  COMMAND(interview, FruitIntoBasket, "FRUITINTOBASKET")                 \
  COMMAND(interview, GuessTheWord, "GUESSTHEWORD")                       \
  COMMAND(interview, LongestIncreasingPathMatrix,                        \
          "LONGESTINCREASINGPATHMATRIX")                                 \
  COMMAND(interview, MedianOfTwoSortedArrays, "MEDIANOFTWOSORTEDARRAYS") \
  COMMAND(interview, MostStonesRemovedWithSameRowOrColumn,               \
          "MOSTSTONESREMOVEDWITHSAMEROWORCOLUMN")                        \
  COMMAND(interview, OddEvenJump, "ODDEVENJUMP")                         \
  COMMAND(interview, RedundantConnection, "REDUNDANTCONNECTION")         \
  COMMAND(interview, UniqueEmailAddresses, "UNIQUEEMAILADDRESSES")       \
  COMMAND(interview, ValidNumber, "VALIDNUMBER")
