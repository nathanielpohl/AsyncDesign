// This file is where commands are registered.
#pragma once

#include "cmd_modules/checksum.h"
#include "cmd_modules/word_count.h"
#include "cmd_modules/word_freq.h"
#include "fpic_modules/fpincppch2.h"

#define LIST_OF_COMMANDS(COMMAND)              \
  COMMAND(cmd_modules, Checksum, "CHECKSUM")   \
  COMMAND(cmd_modules, WordCount, "WORDCOUNT") \
  COMMAND(cmd_modules, WordFreq, "WORDFREQ")   \
  COMMAND(fpic_modules, FPInCppCh2, "FPICCH2")
